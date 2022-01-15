#include <string.h>
#include <iostream>
#include "Content.h"
#include "CharPattern.h"

#define SPACE 's'
#define LINEEND '$'

CharPattern::CharPattern(Rule &rule, uint64_t lineNO, uint64_t colNO, const char fromPattern, bool isEscape): 
	Pattern(rule, lineNO, colNO), m_from_pattern(fromPattern), m_is_from_escape(isEscape) {
		if (!m_is_from_escape) {
			m_from_pattern = PatternMapping(m_from_pattern);
		}
		else {
			switch (m_from_pattern)
			{
			case SPACE:
				m_from_escape_patterns.push_back(' ');
				m_from_escape_patterns.push_back('\t');
				m_from_escape_patterns.push_back('\n');
				break;
			default:
				break;
			}
		}
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
void CharPattern::SetToPattern(char toPattern, bool isEscape){
	m_is_to_escape = isEscape;
	m_to_pattern = toPattern;
	m_to_pattern = PatternMapping(m_to_pattern);
}

bool CharPattern::Compare(const Pattern &other) const {
	if (!IsSameType(other)) {
		return false;
	}
	if (m_from_pattern != m_to_pattern) {
		return Equal(other);
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
	if (!m_from_escape_patterns.empty()) {
		return IsInMultiValue(c);
	}
	return IsInRange(m_from_pattern, m_to_pattern, c);
}
bool CharPattern::IsInRange(char from, char to, char c) const {
	if (from <= to) {
		return from <= c && c <= to;
	}
	else {
		return to <= c && c <= from;
	}
}
const std::string CharPattern::ToString() const {
	return '\'' + m_content + '\'';
}

void CharPattern::CheckMultiValueRange(char pattern, bool isEscape) const {
	if (isEscape) {
		switch (pattern) {
		case SPACE:
			throw std::string("range can not be SPACE!");
			break;
		}
	}
}
char CharPattern::GetFromPattern() {
	return m_from_pattern;
}
bool CharPattern::IsFromEscape() {
	return m_is_from_escape;
}
bool CharPattern::IsInMultiValue(char c) const {
	for (char pattern : m_from_escape_patterns) {
		if (c == pattern) {
			return true;
		}
	}
	return false;
}
char CharPattern::PatternMapping(char src) {
	char dst = src;
	switch (src)
	{
	case LINEEND:
		dst = '\n';
		break;
	default:
		break;
	}
	return dst;
}