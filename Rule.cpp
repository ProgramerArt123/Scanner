#include "RegExpPattern.h"
#include "AndPattern.h"
#include "OrPattern.h"
#include "RepeatPattern.h"
#include "Config.h"
#include "Rule.h"

#define ESCAPE '\\'
#define ROUND_L '('
#define ROUND_R ')'
#define SQUARE_L '['
#define SQUARE_R ']'
#define LABEL '@'
#define ASTERISK '*'
#define PLUS '+'
#define QUESTION '?'

Rule::Rule(Config &config, const std::string literal):
	m_literal(literal.begin(), literal.end()),
	m_pattern(new Pattern),
	m_config(config){
}

void Rule::Parse() {
	while (m_index < m_literal.size()) {
		Parse(*m_pattern);
	}
}

void Rule::Parse(Pattern &parent) {
	switch (m_literal[m_index++])
	{
	case ESCAPE:
		m_index++;
		CharParse(parent);
		break;
	case LABEL:
		LabelParse(parent);
		break;
	case ROUND_L:
		RoundParse(parent);
		break;
	case SQUARE_L:
		SquareParse(parent);
		break;
	default:
		CharParse(parent);
		break;
	}
	if (m_index + 1 < m_literal.size()) {
		std::shared_ptr<Pattern> pattern;
		switch (m_literal[m_index + 1])
		{
		case ASTERISK:
			pattern.reset(new RepeatPattern(0, __UINT64_MAX__));
			break;
		case PLUS:
			pattern.reset(new RepeatPattern(1, __UINT64_MAX__));
			break;
		case QUESTION:
			pattern.reset(new RepeatPattern(0, 1));
			break;
		default :
			break;
		}
		if (pattern) {
			pattern->m_children.push_back(parent.m_children.back());
			parent.m_children.pop_back();
		}
	}
}
void Rule::LabelParse(Pattern &parent) {
	size_t begin = m_index;
	while (m_index < m_literal.size()) {
		if (LABEL == m_literal[m_index++]) {
			const std::string labelName(m_literal.data() + begin, m_index - begin);
			parent.m_children.push_back(m_config.GetRule(labelName).GetPattern());
			return;
		}
	}
	throw std::string("RegExp Format Error, LABEL!");
}
void Rule::RoundParse(Pattern &parent) {
	std::shared_ptr<Pattern> pattern(new AndPattern);
	while (m_index < m_literal.size()) {
		if (ROUND_R == m_literal[m_index]) {
			parent.m_children.push_back(pattern);
			return;
		}
		Parse(*pattern);
	}
	throw std::string("RegExp Format Error, ROUND_L!");
}
void Rule::SquareParse(Pattern &parent) {
	std::shared_ptr<Pattern> pattern(new OrPattern);
	while (m_index < m_literal.size()) {
		if (SQUARE_R == m_literal[m_index]) {
			parent.m_children.push_back(pattern);
			return;
		}
		Parse(*pattern);
	}
	throw std::string("RegExp Format Error, SQUARE_L!");
}
void Rule::CharParse(Pattern &parent) {
	if (m_index >= m_literal.size()) {
		throw std::string("RegExp Format Error, ESCAPE!");
	}
	m_pattern->m_children.push_back(std::shared_ptr<Pattern>
		(new RegExpPattern(m_literal[m_index])));
}

std::shared_ptr<Pattern> &Rule::GetPattern() {
	return m_pattern;
}