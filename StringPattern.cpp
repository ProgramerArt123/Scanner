#include <string.h>
#include <iostream>
#include "Content.h"
#include "StringPattern.h"

StringPattern::StringPattern(Rule &rule, uint64_t lineNO, uint64_t colNO, const std::string pattern): 
	Pattern(rule, lineNO, colNO), m_pattern(pattern) {}
StringPattern::~StringPattern() {}

bool StringPattern::IsMatchOnce(Content &content) const {
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

bool StringPattern::Compare(const Pattern &other) const {
	if (!IsSameType(other)) {
		return false;
	}
	return Equal(other);
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
const std::string StringPattern::ToString() const {
	return '"' + m_content + '"';
}