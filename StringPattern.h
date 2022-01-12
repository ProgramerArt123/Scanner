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
	bool Compare(const Pattern &other) const override;
	bool operator==(const Pattern &other)const override;
	const char *GetTypeName() const override;
	const std::string ToString() const override;
private:
	const std::string m_pattern;
};

#endif