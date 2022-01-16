#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <vector>
#include <map>
#include <memory>
#include <stdint.h>
class Content;
class Rule;
class Pattern {
public:
	explicit Pattern(Rule &rule, uint64_t lineNO, uint64_t colNO);
	virtual ~Pattern();
	bool IsMatch(Content &content)const;
	virtual bool IsMatchOnce(Content &content)const;
	void AddChild(std::shared_ptr<Pattern> child);
	void SetLastChildTimes(uint64_t minTimes, uint64_t maxTimes);
	bool CheckDuplicate(const Pattern &other) const;
	bool IsNotSelf(const Pattern &other) const;
	virtual bool Compare(const Pattern &other) const; 
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
	bool ChildrenCheckDuplicate(const Pattern &other) const;
	void MarkContent(const std::vector<char> &literal, size_t end);
	virtual const std::string ToString() const;
	void ForeachCheckDuplicate(const Pattern &other) const;
	Rule &GetRule()const;
	void BestMatchTracePrint() const;
	void SetParent(const Pattern *parent);
	void CheckClosedLoop(const Content &content)const;
	friend std::ostream &operator<<(std::ostream &os, const Pattern &pattern);
protected:
	
	std::vector<std::shared_ptr<Pattern>> m_children;
	const uint64_t m_line_NO = 0;
	const uint64_t m_col_NO = 0;
	uint64_t m_min_times = 1;
	uint64_t m_max_times = 1;
	std::string m_content;
	Rule &m_rule;
	const Pattern *m_parent = NULL;
};

#endif