#ifndef __STRING_PATTERN_H__
#define __STRING_PATTERN_H__

#include <string>
#include <vector>
#include "Pattern.h"
class StringPattern : public Pattern {
public:
	explicit StringPattern(uint64_t lineNO, uint64_t colNO, const std::string pattern);
	virtual ~StringPattern();
	bool IsMatchOnce(Content &content) override;
private:
	const std::string m_pattern;
};

#endif