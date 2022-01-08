#ifndef __RULE_H__
#define __RULE_H__

#include <string>
#include <vector>
#include <list>
#include <memory>

#include "Pattern.h"
class Rule {
public:
	explicit Rule(const std::string literal);
	void Parse();
private:
	void RoundParse(Pattern &parent, size_t &index);
	void SquareParse(Pattern &parent, size_t &index);
	void CharParse(Pattern &parent, size_t &index);
	void Parse(Pattern &parent, size_t &index);
private:
	const std::vector<char> m_literal;
	Pattern m_pattern;
};

#endif