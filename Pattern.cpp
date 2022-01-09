#include <iostream>
#include <string.h>
#include "Content.h"
#include "Pattern.h"

Pattern::Pattern(uint64_t lineNO, uint64_t colNO):
	m_line_NO(lineNO), m_col_NO(colNO){
}
Pattern::~Pattern() {
	
}
bool Pattern::IsMatch(Content &content) {
	Content::CursorsMemento memento(content);
	uint64_t times = 0;
	while (times++ < m_max_times) {
		if (!IsMatchOnce(content)) {
			break;
		}
	}
	return memento.IsMatch(times > m_min_times);
}
bool Pattern::IsMatchOnce(Content &content) {
	for (const std::shared_ptr<Pattern> &child : m_children) {
		if (!child->IsMatch(content)) {
			return false;
		}
	}
	return true ;
}

void Pattern::AddChild(std::shared_ptr<Pattern> child) {
	m_children.push_back(child);
}

void Pattern::SetLastChildTimes(uint64_t minTimes, uint64_t maxTimes) {
	m_children.back()->m_min_times = minTimes;
	m_children.back()->m_max_times = maxTimes;
}

void Pattern::CheckDuplicate(const Pattern &other) const {
	ChildrenCheckDuplicate(other);
	other.ChildrenCheckDuplicate(*this);
	if (!IsSameType(other)) {
		return;
	}
	for (size_t index = 0; index < m_children.size(); index ++) {
		size_t j = 0;
		if (m_children[index]->SearchEqual(other, j)) {
			if (index + 1 < m_children.size() &&
				m_children[index + 1]->Equal(other, j + 1)) {
				std::cout << "Warn: line:" << m_line_NO << ", col:" << m_col_NO <<
						"<=>line:" << other.m_line_NO << ", col:" << other.m_col_NO << std::endl;
				break;
			}
		}
	}
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
	return this == &other || (*this) == other;
}

bool Pattern::SearchEqual(const Pattern &other, size_t &otherIndex) const {
	if (!IsSameType(other)) {
		return false;
	}
	for (size_t index = 0; index < other.m_children.size(); index++) {
		if (this == &other || (*this) == other) {
			otherIndex = index;
			return true;
		}
	}
	return false;
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
void Pattern::ChildrenCheckDuplicate(const Pattern &other) const {
	for (auto child : m_children) {
		child->CheckDuplicate(other);
	}
}