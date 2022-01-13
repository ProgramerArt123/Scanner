#ifndef __CHAR_PATTERN_H__
#define __CHAR_PATTERN_H__

#include <string>
#include <vector>

#include "Pattern.h"
class CharPattern : public Pattern {
public:
	explicit CharPattern(Rule &rule, uint64_t lineNO, uint64_t colNO, char fromPattern, bool isEscape);
	virtual ~CharPattern();
	bool IsMatchOnce(Content &content) override;
	void SetToPattern(char toPattern);
	bool Compare(const Pattern &other) const override;
	bool operator==(const Pattern &other)const override;
	const char *GetTypeName() const override;
	const std::string ToString() const override;
private:
	bool IsInRange(char c) const;
	const char m_from_pattern;
	char m_to_pattern;
	const bool m_is_escape = false;
};

#endif