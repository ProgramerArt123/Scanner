#ifndef __CHAR_PATTERN_H__
#define __CHAR_PATTERN_H__

#include <string>
#include <vector>
#include "Pattern.h"
class CharPattern : public Pattern {
public:
	explicit CharPattern(char pattern);
	virtual ~CharPattern();
	bool IsMask(Content &content) override;
private:
	const char m_pattern;
};

#endif