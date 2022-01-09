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