#include <iostream>
#include "Content.h"
#include "Pattern.h"

Pattern::Pattern(uint64_t lineNO, uint64_t colNO) :
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
	for (size_t index = 0; index < m_children.size(); index ++) {
		size_t j = 0;
		if (m_children[index]->SearchEqual(other, j)) {
			if (index + 1 < m_children.size() &&
				m_children[index + 1]->Equal(other, j + 1)) {
				std::cout << "Warn: line:" << m_line_NO << ", col:" << m_col_NO <<
						"<=>line:" << other.m_line_NO << ", col:" << other.m_col_NO << std::endl;
				return;
			}
		}
	}

}

bool Pattern::operator==(const Pattern &other) const {
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
	if (otherIndex >= other.m_children.size()) {
		return false;
	}
	return this == &other || (*this) == other;
}

bool Pattern::SearchEqual(const Pattern &other, size_t &otherIndex) const {
	for (size_t index = 0; index < other.m_children.size(); index++) {
		if (this == &other || (*this) == other) {
			otherIndex = index;
			return true;
		}
	}
	return false;
}