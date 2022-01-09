#include <iostream>
#include "Content.h"
#include "OrPattern.h"
OrPattern::OrPattern(uint64_t lineNO, uint64_t colNO):
	Pattern(lineNO, colNO){
	
}
OrPattern::~OrPattern() {}
	
bool OrPattern::IsMatchOnce(Content &content) {
	for (const std::shared_ptr<Pattern> &child : m_children) {
		if (child->IsMatch(content)) {
			return true;
		}
	}
	return false;
}

void OrPattern::CheckDuplicate(const Pattern &other) const {
	ChildrenCheckDuplicate(other);
	other.ChildrenCheckDuplicate(*this);
	if (!IsSameType(other)) {
		return;
	}
	for (size_t i = 0; i < m_children.size(); i++) {
		for (size_t j = 0; i < m_children.size(); j++) {
			if (i != j && m_children[i] == m_children[j]) {
				std::cout << "Warn: line:" << m_line_NO << ", col:" << m_col_NO <<
						"<=>line:" << other.GetLineNO() << ", col:" << other.GetColNO() << std::endl;
				return ;
			}
		}
	}
	for (size_t i = 0; i < m_children.size(); i++) {
		static bool hasDup = false;
		size_t j = 0;
		if (m_children[i]->SearchEqual(other, j)) {
			if (hasDup) {
				std::cout << "Warn: line:" << m_line_NO << ", col:" << m_col_NO <<
					"<=>line:" << other.GetLineNO() << ", col:" << other.GetColNO() << std::endl;
				return ;
			}
			else {
				hasDup = true;
			}
		}
	}
}

const char *OrPattern::GetTypeName() const {
	return "OrPattern";
}