#ifndef __CHAR_PATTERN_H__
#define __CHAR_PATTERN_H__

#include <string>
#include <vector>

#include "Pattern.h"
class CharPattern : public Pattern {
public:
	explicit CharPattern(uint64_t lineNO, uint64_t colNO, char fromPattern);
	virtual ~CharPattern();
	bool IsMatchOnce(Content &content) override;
	void SetToPattern(char toPattern);
	void CheckDuplicate(const Pattern &other) const override;
	bool operator==(const Pattern &other)const override;
	const char *GetTypeName() const override;
private:
	const char m_from_pattern;
	char m_to_pattern;
};

#endif