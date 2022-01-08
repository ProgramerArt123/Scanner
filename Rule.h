#ifndef __RULE_H__
#define __RULE_H__

#include <string>
#include <vector>
#include <list>
#include <memory>

#include "Pattern.h"

class Config;
class Rule {
public:
	explicit Rule(Config &config, const std::string literal);
	void Parse();
	std::shared_ptr<Pattern> &GetPattern();
private:
	void StringParse(Pattern &parent);
	void LabelParse(Pattern &parent);
	void RoundParse(Pattern &parent);
	void SquareParse(Pattern &parent);
	void CharParse(Pattern &parent);
	void Parse(Pattern &parent);
private:
	const std::vector<char> m_literal;
	std::shared_ptr<Pattern> m_pattern;
	Config &m_config;
	size_t m_index = 0;
};

#endif