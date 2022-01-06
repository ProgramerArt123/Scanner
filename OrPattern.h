#ifndef __OR_PATTERN_H__
#define __OR_PATTERN_H__

#include "ListPattern.h"
class OrPattern : public ListPattern{
public:
	virtual ~OrPattern();
	bool IsMask(Content &content) override;
};

#endif