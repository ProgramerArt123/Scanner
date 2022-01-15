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
	void SetToPattern(char toPattern, bool isEscape);
	bool Compare(const Pattern &other) const override;
	bool operator==(const Pattern &other)const override;
	const char *GetTypeName() const override;
	const std::string ToString() const override;
	void CheckMultiValueRange(char pattern, bool isEscape) const;
	char GetFromPattern();
	bool IsFromEscape();
private:
	bool IsInRange(char c) const;
	bool IsInRange(char from, char to, char c) const;
	bool IsInMultiValue(char c) const;
	char PatternMapping(char src);
	char m_from_pattern;
	char m_to_pattern;
	const bool m_is_from_escape = false;
	bool m_is_to_escape = false;
	std::vector<char> m_from_escape_patterns;
};

#endif