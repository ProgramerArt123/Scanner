#ifndef __RULE_H__
#define __RULE_H__

#include <string>
class Rule {
public:
	explicit Rule(const std::string literal);
	void Parse();
private:
	const std::string m_literal;
	
};

#endif