#include <string.h>
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
	bool isMatch = m_from_pattern <= content.GetChar() &&
			content.GetChar() <= m_to_pattern;
	content.Next();
	return isMatch;
}
void CharPattern::SetToPattern(char toPattern) {
	m_to_pattern = toPattern;
}

void CharPattern::Compare(const Pattern &other) const {
}

bool CharPattern::operator==(const Pattern &other)const {
	if (!IsSameType(other)) {
		return false;
	}
	const CharPattern &otherChar = static_cast<const CharPattern &>(other);
	return m_from_pattern == otherChar.m_from_pattern &&
		m_to_pattern == otherChar.m_to_pattern &&
		m_min_times == other.GetMinTimes() &&
		m_max_times == other.GetMaxTimes();
}
const char *CharPattern::GetTypeName() const {
	return "CharPattern";
}