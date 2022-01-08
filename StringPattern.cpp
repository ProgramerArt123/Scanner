#include "Content.h"
#include "StringPattern.h"

StringPattern::StringPattern(uint64_t lineNO, uint64_t colNO, const std::string pattern): 
	Pattern(lineNO, colNO), m_pattern(pattern) {}
StringPattern::~StringPattern() {}

bool StringPattern::IsMask(Content &content)  {
	Content::CursorsMemento memento(content);
	for (const char c : m_pattern) {
		if (content.IsEnd()) {
			return memento.IsMask(false);
		}
		if (c != content.GetChar()) {
			return memento.IsMask(false);
		}
		content.Next();
	}
	return memento.IsMask(true);
}