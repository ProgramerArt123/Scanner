#include "Content.h"
#include "CharPattern.h"

CharPattern::CharPattern(uint64_t lineNO, uint64_t colNO, const char pattern):
	Pattern(lineNO, colNO), m_pattern(pattern) {}
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