#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <vector>
#include <map>
#include <memory>
#include <stdint.h>
class Content;
class Rule;
class Lexical;
enum MATCH_RESULT { 
	MATCH_RESULT_NONE = -1,
	MATCH_RESULT_FAILED = 0,
	MATCH_RESULT_SUCCESS = 1,
	MATCH_RESULT_SUCCESS_JUMP = 2,
};

enum PATTERN_TYPE { 
	PATTERN_TYPE_NONE,
	PATTERN_TYPE_AND,
	PATTERN_TYPE_OR,
	PATTERN_TYPE_STRING,
	PATTERN_TYPE_CHAR
};
class Pattern {
public:
	explicit Pattern(Rule &rule, uint64_t lineNO, uint64_t colNO, PATTERN_TYPE type = PATTERN_TYPE_NONE);
	virtual ~Pattern();
	MATCH_RESULT IsMatch(Content &content, Lexical &parent);
	virtual bool IsMatchOnce(Content &content, Lexical &parent)const;
	void AddChild(std::shared_ptr<Pattern> child);
	void SetLastChildTimes(uint64_t minTimes, uint64_t maxTimes);
	void SetLastChildShortest();
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
	void SetAction(const std::string action);
	virtual const std::string ToString() const;
	const std::string TimesToString() const;	
	void ForeachCheckDuplicate(const Pattern &other) const;
	Rule &GetRule()const;
	void BestMatchTracePrint() const;
	void SetParent(const Pattern *parent);
	void CheckClosedLoop(const Content &content);
	bool IsShortest()const;
	void GetTraceInfo(std::stringstream &trace)const;
	void SetMementoCursor(size_t memento);
	size_t GetMementoCursor()const;
	const std::string &GetActionName()const;
	void TryCommandActionEnter(const Lexical &lexical,  Content &content)const;
	void TryCommandActionExit(const Lexical &lexical, Content &content)const;
	uint64_t GetFlag() const;
	static const std::string  EscapeLiteral(const std::string &src);
	friend std::ostream &operator<<(std::ostream &os, const Pattern &pattern);
protected:
	
	std::vector<std::shared_ptr<Pattern>> m_children;
	const uint64_t m_line_NO = 0;
	const uint64_t m_col_NO = 0;
	uint64_t m_min_times = 1;
	uint64_t m_max_times = 1;
	bool m_is_shortest = false;
	std::string m_content;
	std::string m_action;
	Rule &m_rule;
	const Pattern *m_parent = NULL;
	std::shared_ptr<Pattern> m_next;
	PATTERN_TYPE m_type = PATTERN_TYPE_AND;
	size_t m_memento_cursor = UINT64_MAX;
	uint64_t m_flag = 0;
private:
	bool m_is_closed_loop = false;
};

#endif