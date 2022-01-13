#include <iostream>
#include "Content.h"
#include "OrPattern.h"
OrPattern::OrPattern(Rule &rule, uint64_t lineNO, uint64_t colNO):
	Pattern(rule, lineNO, colNO){
	
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

bool OrPattern::Compare(const Pattern &other) const {
	if (!IsSameType(other)) {
		return false;
	}
	if (!m_is_self_compared) {
		m_is_self_compared = true;
		if (CompareSelf()) {
			return true;
		}
	}
	return CompareOther(other);
}

const char *OrPattern::GetTypeName() const {
	return "OrPattern";
}

bool OrPattern::CompareSelf() const {
	for (size_t i = 0; i < m_children.size(); i++) {
		for (size_t j = 0; i < m_children.size(); j++) {
			if (i != j && m_children[i] == m_children[j]) {
				return true;
			}
		}
	}
	return false;
}

bool OrPattern::CompareOther(const Pattern &other) const {
	bool hasDup = false;
	for (size_t i = 0; i < m_children.size(); i++) {
		size_t j = 0;
		if (m_children[i]->SearchEqual(other, j)) {
			if (hasDup) {
				return true;
			}
			else {
				hasDup = true;
			}
		}
	}
	return false;
}

const std::string OrPattern::ToString() const {
	return '[' + m_content + ']';
}