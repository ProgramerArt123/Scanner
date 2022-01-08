#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <list>
#include <memory>
#include <stdint.h>
class Content;
class Pattern {
public:
	explicit Pattern(uint64_t lineNO, uint64_t colNO);
	virtual ~Pattern();
	bool IsMask(Content &content);
	virtual bool IsMaskOnce(Content &content);
	void AddChild(std::shared_ptr<Pattern> child);
	void SetLastChildTimes(uint64_t minTimes, uint64_t maxTimes);
protected:
	std::list<std::shared_ptr<Pattern>> m_children;
	const uint64_t m_line_NO = 0;
	const uint64_t m_col_NO = 0;
	uint64_t m_min_times = 1;
	uint64_t m_max_times = 1;
};

#endif