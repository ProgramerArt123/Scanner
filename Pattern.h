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
	void CheckDuplicate(const Pattern &other) const;
	virtual void Compare(const Pattern &other) const; 
	virtual bool operator==(const Pattern &other)const;
	bool Equal(const Pattern &other, size_t otherIndex) const;
	bool SearchEqual(const Pattern &other, size_t &otherIndex) const;
	bool Equal(const Pattern &other) const;
	bool IsSameType(const Pattern &other)const;
	uint64_t GetLineNO () const;
	uint64_t GetColNO () const;
	uint64_t GetMinTimes() const;
	uint64_t GetMaxTimes() const;
	virtual const char *GetTypeName() const;
	void ChildrenCheckDuplicate(const Pattern &other) const;
	void MarkContent(const std::vector<char> &literal, size_t end);
	friend std::ostream &operator<<(std::ostream &os, const Pattern &pattern);
protected:
	
	std::vector<std::shared_ptr<Pattern>> m_children;
	const uint64_t m_line_NO = 0;
	const uint64_t m_col_NO = 0;
	uint64_t m_min_times = 1;
	uint64_t m_max_times = 1;
	std::string m_content;
};

#endif