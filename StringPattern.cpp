#include "Content.h"
#include "StringPattern.h"

StringPattern::StringPattern(const std::string pattern): 
	m_pattern(pattern) {}
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