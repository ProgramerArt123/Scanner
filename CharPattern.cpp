#include <string.h>
#include <iostream>
#include "Content.h"
#include "CharPattern.h"

CharPattern::CharPattern(uint64_t lineNO, uint64_t colNO, const char fromPattern): 
	Pattern(lineNO, colNO), m_from_pattern(fromPattern) {
		m_to_pattern = m_from_pattern;
}
CharPattern::~CharPattern() {}

bool CharPattern::IsMatchOnce(Content &content) {
	if (content.IsEnd()) {
		return false;
	}
	bool isMatch = IsInRange(content.GetChar());
	content.Next();
	return isMatch;
}
void CharPattern::SetToPattern(char toPattern) {
	m_to_pattern = toPattern;
}

void CharPattern::Compare(const Pattern &other) const {
	if (!IsSameType(other)) {
		return;
	}
	if (m_from_pattern != m_to_pattern) {
		if (Equal(other)) {
			std::cout << "Warn: line:" << m_line_NO << ", col:" << m_col_NO <<
						"<=>line:" << other.GetLineNO() << ", col:" << other.GetColNO() << std::endl;
		}
	}
}

bool CharPattern::operator==(const Pattern &other)const {
	if (!IsSameType(other)) {
		return false;
	}
	const CharPattern &otherChar = static_cast<const CharPattern &>(other);
	return ((m_from_pattern == otherChar.m_from_pattern &&
		m_to_pattern == otherChar.m_to_pattern) ||
		(m_from_pattern == otherChar.m_to_pattern &&
		m_to_pattern == otherChar.m_from_pattern)) &&
		m_min_times == other.GetMinTimes() &&
		m_max_times == other.GetMaxTimes();
}
const char *CharPattern::GetTypeName() const {
	return "CharPattern";
}

bool CharPattern::IsInRange(char c) const {
	if (m_from_pattern <= m_to_pattern) {
		return m_from_pattern <= c &&
			c <= m_to_pattern;
	}
	else {
		return m_to_pattern <= c &&
			c <= m_from_pattern;
	}
}