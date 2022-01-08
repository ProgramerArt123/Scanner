#ifndef __REG_EXP_PATTERN_H__
#define __REG_EXP_PATTERN_H__

#include <string>
#include <vector>
#include "Pattern.h"
class RegExpPattern : public Pattern {
public:
	explicit RegExpPattern(char pattern);
	virtual ~RegExpPattern();
	bool IsMask(Content &content) override;
private:
	const char m_pattern;
};

#endif