#include <iostream>
#include <string.h>
#include <unistd.h>
#include "Content.h"
#include "Config.h"
#include "Rule.h"
#include "Pattern.h"

Pattern::Pattern(Rule &rule, uint64_t lineNO, uint64_t colNO):
	m_rule(rule),m_line_NO(lineNO), m_col_NO(colNO){
}
Pattern::~Pattern() {
	
}
MATCH_RESULT Pattern::IsMatch(Content &content)const {
	CheckClosedLoop(content);
	Content::CursorsMemento memento(content);
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
	if (times > m_min_times) {
		std::cout << "Match:" << *this << "==============================" << content.GetMemInfo() << std::endl;
	}
	else {
		//std::cout << "UnMatch:" << *this << "*" << content.GetMemInfo() << std::endl;
	}
	if (!isNextMatch) {
		if (memento.IsMatch(times > m_min_times)) {
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
	return '(' + m_content + ')';
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
	const Pattern *parent = m_parent;
	while (parent) {
		if (parent == this && content.NotForward()) {
			throw m_content + " Closed Loop";
		}
		parent = parent->m_parent;
	}
}

bool Pattern::IsShortest()const {
	return m_is_shortest;
}