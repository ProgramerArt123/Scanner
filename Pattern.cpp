#include <iostream>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include "Content.h"
#include "Config.h"
#include "Rule.h"
#include "Pattern.h"

Pattern::Pattern(Rule &rule, uint64_t lineNO, uint64_t colNO, PATTERN_TYPE type):
	m_rule(rule),m_line_NO(lineNO), m_col_NO(colNO), m_type(type){
}
Pattern::~Pattern() {
	
}
MATCH_RESULT Pattern::IsMatch(Content &content)  {
	CheckClosedLoop(content);
	Content::CursorsMemento memento(content, *this);
	bool isNextMatch = false;
	uint64_t times = 0;
	while (times++ < m_max_times) {
		if (!IsMatchOnce(content)) {
			break;
		}
		if (IsShortest() && m_next && times > m_min_times) {
			if (m_next->IsMatch(content)) {
				isNextMatch = true;
				break;
			}
		}
	}
	if (m_rule.GetName() != "ignore") {
		std::stringstream trace;
		GetTraceInfo(trace);
		if (times > m_min_times) {
			std::cout << "Match:" << *this << "===" << content.GetMemInfo(memento) << trace.str() << std::endl;
		}
		else {
			std::cout << "UnMatch:" << *this << "***" << content.GetMemInfo(memento) << trace.str() << std::endl;
		}
	}
	memento.IsMatch(isNextMatch || times > m_min_times);
	if (!isNextMatch) {
		if (times > m_min_times) {
			return MATCH_RESULT_SUCCESS;
		}
		else {
			return MATCH_RESULT_FAILED;
		}
	}
	else {
		return MATCH_RESULT_SUCCESS_JUMP;
	}
}
bool Pattern::IsMatchOnce(Content &content) const {
	size_t count = m_children.size();
	for (size_t index = 0; index < count; index ++) {
		m_children[index]->SetParent(this);
		MATCH_RESULT match = m_children[index]->IsMatch(content);
		if (MATCH_RESULT_FAILED == match) {
			return false;
		}
		else if (MATCH_RESULT_SUCCESS_JUMP == match) {
			index++;
		}
	}
	return true ;
}

void Pattern::AddChild(std::shared_ptr<Pattern> child) {
	std::shared_ptr<Pattern> last;
	if (!m_children.empty()) {
		last = m_children.back();
	}
	m_children.push_back(child);
	child->SetParent(this);
	if (last && last->IsShortest()) {
		last->m_next = child;
	}
}

void Pattern::SetLastChildTimes(uint64_t minTimes, uint64_t maxTimes) {
	m_children.back()->m_min_times = minTimes;
	m_children.back()->m_max_times = maxTimes;
}

void Pattern::SetLastChildShortest() {
	m_children.back()->m_is_shortest = true;
}

bool Pattern::CheckDuplicate(const Pattern &other) const {
	if (!IsNotSelf(other)) {
		return false;
	}
	usleep(500000);
	if (!Compare(other)) {
		std::cout << *this << "****" << other << std::endl;
		return ChildrenCheckDuplicate(other);
	}
	else {
		std::cout << *this << "====" << other << std::endl ;
		return true;
	}
}

bool Pattern::Compare(const Pattern &other) const {
	if (!IsSameType(other)) {
		return false;
	}
	for (size_t index = 0; index < m_children.size(); index++) {
		size_t j = 0;
		if (m_children[index]->SearchEqual(other, j)) {
			if (index + 1 < m_children.size() &&
				m_children[index + 1]->Equal(other, j + 1)) {
				return true;
			}
		}
	}
	return false;
}

bool Pattern::operator==(const Pattern &other) const {
	if (!IsSameType(other)) {
		return false;
	}
	if (m_children.size() != other.m_children.size()) {
		return false;
	}
	for (size_t index = 0; index < m_children.size(); index++) {
		if (m_children[index] != other.m_children[index]) {
			return false;
		}
	}
	return true;
}

bool Pattern::Equal(const Pattern &other, size_t otherIndex) const {
	if (!IsSameType(other)) {
		return false;
	}
	if (otherIndex >= other.m_children.size()) {
		return false;
	}
	return Equal(*other.m_children[otherIndex]);
}

bool Pattern::SearchEqual(const Pattern &other, size_t &otherIndex) const {
	if (!IsSameType(other)) {
		return false;
	}
	for (size_t index = 0; index < other.m_children.size(); index++) {
		if (Equal(*other.m_children[index])) {
			otherIndex = index;
			return true;
		}
	}
	return false;
}
bool Pattern::Equal(const Pattern &other) const {
	return this == &other || (*this) == other;
}
uint64_t Pattern::GetLineNO() const {
	return m_line_NO;
}
uint64_t Pattern::GetColNO() const {
	return m_col_NO;
}
uint64_t Pattern::GetMinTimes() const {
	return m_min_times;
}
uint64_t Pattern::GetMaxTimes() const {
	return m_max_times;
}
const char *Pattern::GetTypeName() const {
	return "Pattern";
}
bool Pattern::IsSameType(const Pattern &other)const {
	return 0 == strcmp(GetTypeName(), other.GetTypeName());
}
bool Pattern::ChildrenCheckDuplicate(const Pattern &other) const {
	for (auto child : m_children) {
		if (child->CheckDuplicate(other)) {
			return true;
		}
	}
	return false;
}
void Pattern::MarkContent(const std::vector<char> &literal, size_t end) {
	m_content.assign(literal.begin() + m_col_NO, literal.begin() + end);
}

const std::string Pattern::ToString() const {
	return '(' + m_content + ')' + TimesToString();
}

const std::string Pattern::TimesToString() const {
	return "{" + std::to_string(m_min_times) + 
		"," + std::to_string(m_max_times) + "}";
}

void Pattern::ForeachCheckDuplicate(const Pattern &other) const {
	other.CheckDuplicate(*this);
	if (IsNotSelf(other)) {
		for (auto child : m_children) {
			child->ForeachCheckDuplicate(other);
		}
	}
}
Rule &Pattern::GetRule() const {
	return m_rule;
}
bool Pattern::IsNotSelf(const Pattern &other) const {
	return m_line_NO != other.m_line_NO || m_col_NO != other.m_col_NO;
}
std::ostream &operator<<(std::ostream &os, const Pattern &pattern) {
	os << "【line:" << pattern.m_line_NO << ",col:" << 
		pattern.m_col_NO << ",content:" << pattern.ToString() << "】";
	return os;
}

void Pattern::BestMatchTracePrint() const {
	std::cout << *this << std::endl;
	if (m_parent) {
		m_parent->BestMatchTracePrint();
	}
}
void Pattern::SetParent(const Pattern *parent) {
	m_parent = parent;
}

void Pattern::CheckClosedLoop(const Content &content) const {
	const Pattern *backward = m_parent;
	while (backward) {
		if (backward == this) {
			if (backward->GetMementoCursor() && content.GetCursor()) {
				throw m_content + " Closed Loop";
			}
			return;
		}
		backward = backward->m_parent;
	}
}

bool Pattern::IsShortest()const {
	return m_is_shortest;
}

void Pattern::GetTraceInfo(std::stringstream &trace) const {
	trace << "<-" << GetRule().GetName();
	const Pattern *backward = m_parent;
	while (backward) {
		if (backward == this) {
			return;
		}
		trace << "<-" << backward->GetRule().GetName();
		backward = backward->m_parent;
	}
}

void Pattern::SetMementoCursor(size_t memento) {
	m_memento_cursor = memento;
}
size_t Pattern::GetMementoCursor()const {
	return m_memento_cursor;
}