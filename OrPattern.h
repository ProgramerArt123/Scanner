#ifndef __OR_PATTERN_H__
#define __OR_PATTERN_H__

#include "Pattern.h"
class OrPattern : public Pattern {
public:
	explicit OrPattern(uint64_t lineNO, uint64_t colNO);
	virtual ~OrPattern();
	bool IsMatchOnce(Content &content) override;
	bool Compare(const Pattern &other) const override;
	const char *GetTypeName() const override;
	const std::string ToString() const override;
private:
	mutable bool m_is_self_compared = false;
	bool CompareSelf() const;
	bool CompareOther(const Pattern &other) const;
};

#endif