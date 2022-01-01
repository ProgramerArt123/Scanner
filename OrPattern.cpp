#include <iostream>
#include "Content.h"
#include "CodeGenerate.h"
#include "Rule.h"
#include "OrPattern.h"
OrPattern::OrPattern(Rule &rule, uint64_t lineNO, uint64_t colNO):
	Pattern(rule, lineNO, colNO, PATTERN_TYPE_OR){
		CodeGenerate::GetInstance().GetSourceStream() <<
		"\tstd::shared_ptr<Pattern> pattern" << m_flag << "(new OrPattern(*rule" << rule.GetFlag() << ", " << lineNO << ", " << colNO << "));"
		<< std::endl;
}
OrPattern::~OrPattern() {}
	
bool OrPattern::IsMatchOnce(Content &content, Lexical &parent)const {
	for (const TimesPattern &child : m_children) {
		child.m_pattern->SetParent(this);
		if (child.m_pattern->IsMatch(child.m_min_times, 
				child.m_max_times, content, parent)) {
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
			if (i != j && m_children[i].m_pattern == m_children[j].m_pattern) {
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
		if (m_children[i].m_pattern->SearchEqual(other, j)) {
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