#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <vector>
#include <memory>
#include <stdint.h>
class Content;
class Pattern {
public:
	explicit Pattern(uint64_t lineNO, uint64_t colNO);
	virtual ~Pattern();
	bool IsMatch(Content &content);
	virtual bool IsMatchOnce(Content &content);
	void AddChild(std::shared_ptr<Pattern> child);
	void SetLastChildTimes(uint64_t minTimes, uint64_t maxTimes);
	virtual void CheckDuplicate(const Pattern &other) const;
	virtual bool operator==(const Pattern &other)const;
	bool Equal(const Pattern &other, size_t otherIndex) const;
	bool SearchEqual(const Pattern &other, size_t &otherIndex) const;
protected:
	std::vector<std::shared_ptr<Pattern>> m_children;
	const uint64_t m_line_NO = 0;
	const uint64_t m_col_NO = 0;
	uint64_t m_min_times = 1;
	uint64_t m_max_times = 1;
};

#endif