#ifndef __OR_PATTERN_H__
#define __OR_PATTERN_H__

#include "Pattern.h"
class OrPattern : public Pattern {
public:
	explicit OrPattern(uint64_t lineNO, uint64_t colNO);
	virtual ~OrPattern();
	bool IsMaskOnce(Content &content) override;
};

#endif