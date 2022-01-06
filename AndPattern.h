#ifndef __AND_PATTERN_H__
#define __AND_PATTERN_H__

#include "ListPattern.h"
class AndPattern : public ListPattern {
public:
	virtual ~AndPattern();
	bool IsMask(Content &content) override;
};

#endif