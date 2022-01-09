#include <string.h>
#include "Content.h"
#include "StringPattern.h"

StringPattern::StringPattern(uint64_t lineNO, uint64_t colNO, const std::string pattern): 
	Pattern(lineNO, colNO), m_pattern(pattern) {}
StringPattern::~StringPattern() {}

bool StringPattern::IsMatchOnce(Content &content) {
	for (const char c : m_pattern) {
		if (content.IsEnd()) {
			return false;
		}
		if (c != content.GetChar()) {
			return false;
		}
		content.Next();
	}
	return true;
}

void StringPattern::CheckDuplicate(const Pattern &other) const {
	
}
bool StringPattern::operator==(const Pattern &other)const {
	if (!IsSameType(other)) {
		return false;
	}
	const StringPattern &otherChar = static_cast<const StringPattern &>(other);
	return m_pattern == otherChar.m_pattern &&
		m_min_times == other.GetMinTimes() &&
		m_max_times == other.GetMaxTimes();
}
const char *StringPattern::GetTypeName() const {
	return "StringPattern";
}