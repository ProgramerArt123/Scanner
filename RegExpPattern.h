#ifndef __REG_EXP_PATTERN_H__
#define __REG_EXP_PATTERN_H__

#include <string>
#include "Pattern.h"
class RegExpPattern : public Pattern {
public:
	explicit RegExpPattern(const std::string pattern);
	virtual ~RegExpPattern();
	bool IsMask(Content &content) override;
private:
	const std::string m_pattern;
};

#endif