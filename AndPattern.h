#ifndef __AND_PATTERN_H__
#define __AND_PATTERN_H__

#include "Pattern.h"
class AndPattern : public Pattern {
public:
	virtual ~AndPattern();
	bool IsMask(Content &content) override;
};

#endif