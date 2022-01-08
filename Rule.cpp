#include "RegExpPattern.h"
#include "AndPattern.h"
#include "OrPattern.h"
#include "RepeatPattern.h"
#include "Rule.h"

#define ESCAPE '\\'
#define ROUND_L '('
#define ROUND_R ')'
#define SQUARE_L '['
#define SQUARE_R ']'
#define ASTERISK '*'
#define PLUS '+'
#define QUESTION '?'

Rule::Rule(const std::string literal):
	m_literal(literal.begin(), literal.end()){
}

void Rule::Parse() {
	size_t index = 0;
	while (index < m_literal.size()) {
		Parse(m_pattern, index);
	}
}

void Rule::Parse(Pattern &parent, size_t &index) {
	switch (m_literal[index++])
	{
	case ESCAPE:
		index++;
		CharParse(parent, index);
		break;
	case ROUND_L:
		RoundParse(parent, index);
		break;
	case SQUARE_L:
		SquareParse(parent, index);
		break;
	default:
		CharParse(parent, index);
		break;
	}
	if (index + 1 < m_literal.size()) {
		std::shared_ptr<Pattern> pattern;
		switch (m_literal[index + 1])
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
void Rule::RoundParse(Pattern &parent, size_t &index) {
	std::shared_ptr<Pattern> pattern(new AndPattern);
	while (index < m_literal.size()) {
		if (ROUND_R == m_literal[index]) {
			parent.m_children.push_back(pattern);
			return;
		}
		Parse(*pattern, index);
	}
	throw std::string("RegExp Format Error, ROUND_L!");
}
void Rule::SquareParse(Pattern &parent, size_t &index) {
	std::shared_ptr<Pattern> pattern(new OrPattern);
	while (index < m_literal.size()) {
		if (SQUARE_R == m_literal[index]) {
			parent.m_children.push_back(pattern);
			return;
		}
		Parse(*pattern, index);
	}
	throw std::string("RegExp Format Error, SQUARE_L!");
}
void Rule::CharParse(Pattern &parent, size_t &index) {
	if (index >= m_literal.size()) {
		throw std::string("RegExp Format Error, ESCAPE!");
	}
	m_pattern.m_children.push_back(std::shared_ptr<Pattern>
		(new RegExpPattern(m_literal[index])));
}