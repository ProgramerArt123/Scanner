#ifndef __AND_PATTERN_H__
#define __AND_PATTERN_H__

#include "Pattern.h"
class AndPattern : public Pattern {
public:
	explicit AndPattern(Rule &rule, uint64_t lineNO, uint64_t colNO);
};

#endif