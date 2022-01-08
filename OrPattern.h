#ifndef __OR_PATTERN_H__
#define __OR_PATTERN_H__

#include "Pattern.h"
class OrPattern : public Pattern {
public:
	virtual ~OrPattern();
	bool IsMask(Content &content) override;
};

#endif