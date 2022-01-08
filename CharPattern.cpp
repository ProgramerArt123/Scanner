#include "Content.h"
#include "CharPattern.h"

CharPattern::CharPattern(const char pattern): 
	m_pattern(pattern) {}
CharPattern::~CharPattern() {}

bool CharPattern::IsMask(Content &content)  {
	Content::CursorsMemento memento(content);
	if (content.IsEnd()) {
		return memento.IsMask(false);
	}
	bool isMask = m_pattern == content.GetChar();
	content.Next();
	return memento.IsMask(isMask);
}