#include <iostream>
#include "CharPattern.h"
#include "StringPattern.h"
#include "OrPattern.h"
#include "Config.h"
#include "Rule.h"

#define ESCAPE '\\'
#define ROUND_L '('
#define ROUND_R ')'
#define SQUARE_L '['
#define SQUARE_R ']'
#define LABEL '@'
#define STRING '"'
#define ASTERISK '*'
#define PLUS '+'
#define QUESTION '?'
#define RANGE '-'
#define LINEEND '$'

Rule::Rule(Config &config, const std::string name, const std::string literal, uint64_t lineNO):
	m_config(config),m_name(name),
	m_literal(literal.begin(), literal.end()),
	m_pattern(new Pattern(*this, lineNO, 0)),
	m_line_NO(lineNO){
}

void Rule::Parse() {
	while (m_index < m_literal.size()) {
		Parse(*m_pattern);
	}
	m_pattern->MarkContent(m_literal, m_index);
}

void Rule::Parse(Pattern &parent) {
	switch (m_literal[m_index])
	{
	case ESCAPE:
		m_index++;
		CharParse(parent, true);
		break;
	case LABEL:
		m_index++;
		LabelParse(parent);
		break;
	case STRING:
		m_index++;
		StringParse(parent);
		break;
	case ROUND_L:
		m_index++;
		RoundParse(parent);
		break;
	case SQUARE_L:
		m_index++;
		SquareParse(parent);
		break;
	default:
		CharParse(parent, false);
		break;
	}
	
	if (m_index < m_literal.size()) {
		switch (m_literal[m_index])
		{
		case ASTERISK:
			m_index++;
			parent.SetLastChildTimes(0, __UINT64_MAX__);
			break;
		case PLUS:
			m_index++;
			parent.SetLastChildTimes(1, __UINT64_MAX__);
			break;
		case QUESTION:
			m_index++;
			parent.SetLastChildTimes(0, 1);
			break;
		default :
			break;
		}
	}
}

void Rule::StringParse(Pattern &parent) {
	size_t begin = m_index;
	while (m_index < m_literal.size()) {
		if (STRING == m_literal[m_index++]) {
			const std::string pattern(m_literal.data() + begin, m_index - 1 - begin);
			StringPattern *string = new StringPattern(*this, m_line_NO, begin, pattern);
			string->MarkContent(m_literal, m_index - 1);
			parent.AddChild(std::shared_ptr<Pattern>(string));
			return;
		}
	}
	throw std::string("Config Format Error, STRING!");
}
void Rule::LabelParse(Pattern &parent) {
	size_t begin = m_index;
	while (m_index < m_literal.size()) {
		if (LABEL == m_literal[m_index++]) {
			const std::string labelName(m_literal.data() + begin, m_index - 1 - begin);
			parent.AddChild(m_config.GetRule(labelName).GetPattern());
			return;
		}
	}
	throw std::string("Config Format Error, LABEL!");
}
void Rule::RoundParse(Pattern &parent) {
	std::shared_ptr<Pattern> pattern(new Pattern(*this, m_line_NO, m_index));
	while (m_index < m_literal.size()) {
		Parse(*pattern);
		if (ROUND_R == m_literal[m_index]) {
			pattern->MarkContent(m_literal, m_index);
			parent.AddChild(pattern);
			m_index++;
			TryActionParse(*pattern);
			return;
		}
	}
	throw std::string("Config Format Error, ROUND_L!");
}
void Rule::SquareParse(Pattern &parent) {
	std::shared_ptr<Pattern> pattern(new OrPattern(*this, m_line_NO, m_index));
	while (m_index < m_literal.size()) {
		Parse(*pattern);
		if (SQUARE_R == m_literal[m_index]) {
			pattern->MarkContent(m_literal, m_index);
			parent.AddChild(pattern) ;
			m_index++;
			return;
		}
	}
	throw std::string("Config Format Error, SQUARE_L!");
}
void Rule::CharParse(Pattern &parent, bool isEscape) {
	if (m_index >= m_literal.size()) {
		throw std::string("Config Format Error, ESCAPE!");
	}
	char c;
	if (!isEscape) {
		switch (m_literal[m_index])
		{
		case LINEEND:
			c = '\n';
			break;
		default:
			c = m_literal[m_index];
			break;
		}
	}
	CharPattern *charPattern = new CharPattern(*this, m_line_NO, m_index, c, isEscape);
	m_pattern->AddChild(std::shared_ptr<Pattern>(charPattern));
	m_index++;
	TryRangeParse(*charPattern);
	charPattern->MarkContent(m_literal, m_index);
}
void Rule::TryRangeParse(CharPattern &character) {
	if (m_index + 1 < m_literal.size()) {
		if (RANGE == m_literal[m_index ]) {
			if (ESCAPE != m_literal[m_index + 1]) {
				character.SetToPattern(m_literal[m_index + 1]);
				m_index += 2;
			}
			else {
				if (m_index + 2 >= m_literal.size()) {
					throw std::string("RegExp Format Error, RANGE!");
				}
				character.SetToPattern(m_literal[m_index + 2]);
				m_index += 3;
			}
		}
	}
}
void Rule::TryActionParse(Pattern &round) {
	
}
std::shared_ptr<Pattern> &Rule::GetPattern() {
	return m_pattern;
}

void Rule::CheckDuplicate(const Pattern &other) {
	m_pattern->CheckDuplicate(other);
}

void Rule::Foreach(std::map<std::string, std::unique_ptr<Rule>>::iterator current) const {
	m_pattern->Foreach(current);
}
Config &Rule::GetConfig() {
	return m_config;
}
