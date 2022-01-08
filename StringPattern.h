#ifndef __STRING_PATTERN_H__
#define __STRING_PATTERN_H__

#include <string>
#include <vector>
#include "Pattern.h"
class StringPattern : public Pattern {
public:
	explicit StringPattern(const std::string pattern);
	virtual ~StringPattern();
	bool IsMask(Content &content) override;
private:
	const std::string m_pattern;
};

#endif