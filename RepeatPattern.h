#ifndef __REPEAT_PATTERN_H__
#define __REPEAT_PATTERN_H__

#include <memory>
#include <stdint.h>
#include "Pattern.h"
class RepeatPattern : public Pattern {
public:
	explicit RepeatPattern(uint64_t minTimes, uint64_t maxTimes);
	virtual ~RepeatPattern();
	bool IsMask(Content &content) override;
private:
	uint64_t m_min_times = 1;
	uint64_t m_max_times = 1;
};

#endif