#include <iostream>
#include "CharPattern.h"
#include "StringPattern.h"
#include "OrPattern.h"
#include "AndPattern.h"
#include "Config.h"
#include "Content.h"
#include "CodeGenerate.h"
#include "Rule.h"

#define ESCAPE '\\'
#define EXCLUDE '^'
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
#define ACTION '#'

Rule::Rule(Config &config, const std::string name, const std::string literal, uint64_t lineNO):
	m_config(config),m_name(name),
	m_literal(literal.begin(), literal.end()),
	m_pattern(new Pattern(*this, lineNO, 0)),
	m_line_NO(lineNO){
		static uint64_t flag = 0;
		m_flag = flag++;
		std::cout << "Rule *rule" << m_flag << " = new Rule(config, " << name << ", " << literal << ", " << lineNO << ");" << std::endl;
		CodeGenerate::GetInstance().GetStream() <<
		"Rule *rule" << m_flag << " = new Rule(config, " << name << ", " << literal << ", " << lineNO << ");"
		<< std::endl;
}

void Rule::Parse() {
	while (m_index < m_literal.size()) {
		Parse(*m_pattern);
	}
	m_pattern->MarkContent(m_literal, m_index);
}

void Rule::Parse(Pattern &parent) {
	bool isExclude = false;
	if (EXCLUDE == m_literal[m_index]) {
		isExclude = true;
		m_index++;
		if (m_index >= m_literal.size()) {
			throw std::string("Config Format Error, EXCLUDE!");
		}
	}
	switch (m_literal[m_index])
	{
	case ESCAPE:
		m_index++;
		CharParse(parent, true, isExclude);
		break;
	case LABEL:
		if (isExclude) {
			throw std::string("EXCLUDE unsupport LABEL");
		}
		m_index++;
		LabelParse(parent);
		break;
	case STRING:
		m_index++;
		StringParse(parent);
		break;
	case ROUND_L:
		if (isExclude) {
			throw std::string("EXCLUDE unsupport ROUND");
		}
		m_index++;
		RoundParse(parent);
		break;
	case SQUARE_L:
		if (isExclude) {
			throw std::string("EXCLUDE unsupport SQUARE");
		}
		m_index++;
		SquareParse(parent);
		break;
	default:
		CharParse(parent, false, isExclude);
		break;
	}
	
	if (m_index < m_literal.size()) {
		uint64_t minTimes = 1;
		uint64_t maxTimes = 1;
		switch (m_literal[m_index])
		{
		case ASTERISK:
			minTimes = 0, maxTimes = __UINT64_MAX__;
			break;
		case PLUS:
			minTimes = 1, maxTimes = __UINT64_MAX__;
			break;
		case QUESTION:
			minTimes = 0, maxTimes = 1;
			break;
		default :
			return;
			break;
		}
		
		m_index++;
		parent.SetLastChildTimes(minTimes, maxTimes);
		if (m_index < m_literal.size() && m_literal[m_index] == QUESTION) {
			m_index++;
			parent.SetLastChildShortest();
		}
	}
}

void Rule::StringParse(Pattern &parent) {
	size_t begin = m_index;
	while (m_index < m_literal.size()) {
		if (STRING == m_literal[m_index++]) {
			const std::string pattern(m_literal.data() + begin, m_index - 1 - begin);
			StringPattern *string = new StringPattern(*this, m_line_NO, begin, pattern);
			parent.AddChild(std::shared_ptr<Pattern>(string));
			string->MarkContent(m_literal, m_index - 1);
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
			std::shared_ptr<Pattern> pattern(m_config.GetRule(labelName).GetPattern());
			parent.AddChild(pattern);
			return;
		}
	}
	throw std::string("Config Format Error, LABEL!");
}
void Rule::RoundParse(Pattern &parent) {
	std::shared_ptr<Pattern> pattern(new AndPattern(*this, m_line_NO, m_index));
	parent.AddChild(pattern);
	while (m_index < m_literal.size()) {
		Parse(*pattern);
		if (ROUND_R == m_literal[m_index]) {
			pattern->MarkContent(m_literal, m_index);
			m_index++;
			if (m_index < m_literal.size() &&
				ACTION == m_literal[m_index]) {
				m_index++;
				TryActionParse(*pattern);
			}
			return;
		}
	}
	throw std::string("Config Format Error, ROUND_L!");
}
void Rule::SquareParse(Pattern &parent) {
	std::shared_ptr<Pattern> pattern(new OrPattern(*this, m_line_NO, m_index));
	parent.AddChild(pattern);
	while (m_index < m_literal.size()) {
		Parse(*pattern);
		if (SQUARE_R == m_literal[m_index]) {
			pattern->MarkContent(m_literal, m_index);
			m_index++;
			return;
		}
	}
	throw std::string("Config Format Error, SQUARE_L!");
}
void Rule::CharParse(Pattern &parent, bool isEscape, bool isExclude) {
	if (m_index >= m_literal.size()) {
		throw std::string("Config Format Error, ESCAPE!");
	}
	CharPattern *charPattern = new CharPattern(*this, m_line_NO, m_index, 
		m_literal[m_index], isEscape, isExclude);
	parent.AddChild(std::shared_ptr<Pattern>(charPattern));
	m_index++;
	TryRangeParse(*charPattern);
	charPattern->MarkContent(m_literal, m_index);
}

void Rule::TryRangeParse(CharPattern &character) {
	if (m_index + 1 < m_literal.size()) {
		if (RANGE == m_literal[m_index]) {
			character.CheckMultiValueRange(character.GetFromPattern(), 
				character.IsFromEscape());
			if (ESCAPE != m_literal[m_index + 1]) {
				character.CheckMultiValueRange(m_literal[m_index + 1], false);
				character.SetToPattern(m_literal[m_index + 1], false);
				m_index += 2;
			}
			else {
				if (m_index + 2 >= m_literal.size()) {
					throw std::string("RegExp Format Error, RANGE!");
				}
				character.CheckMultiValueRange(m_literal[m_index + 2], true);
				character.SetToPattern(m_literal[m_index + 2], true);
				m_index += 3;
			}
		}
	}
}
void Rule::TryActionParse(Pattern &round) {
	size_t begin = m_index;
	while (m_index < m_literal.size()) {
		if (ACTION == m_literal[m_index++]) {
			const std::string action(m_literal.data() + begin, m_index - 1 - begin);
			round.SetAction(action);
			return;
		}
	}
	throw std::string("Config Format Error, ACTION!");
}
std::shared_ptr<Pattern> &Rule::GetPattern() {
	return m_pattern;
}

void Rule::CheckDuplicate(const Rule &other) {
	m_pattern->ForeachCheckDuplicate(*other.m_pattern);
}

Config &Rule::GetConfig() {
	return m_config;
}

bool Rule::IsMatch(Content &content)const {
	return m_pattern->IsMatch(content, 
		content.GetLexicalRoot());
}
const std::string &Rule::GetName() {
	return m_name;
}

uint64_t Rule::GetFlag() const {
	return m_flag;
}