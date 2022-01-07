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
	uint64_t m_min_times = 0;
	uint64_t m_max_times = UINT64_MAX;
	std::unique_ptr<Pattern> m_single;
};

#endif