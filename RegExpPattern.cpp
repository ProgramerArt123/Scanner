#include "Content.h"
#include "RegExpPattern.h"

#define ESCAPE '\\'
#define ROUND_L '('
#define ROUND_R ')'
#define SQUARE_L '['
#define SQUARE_R ']'
#define ASTERISK '*'
#define PLUS '+'
#define QUESTION '?'

RegExpPattern::RegExpPattern(const char pattern)
	: m_pattern(pattern) {}
RegExpPattern::~RegExpPattern() {}

bool RegExpPattern::IsMask(Content &content)  {
	Content::CursorsMemento memento(content);
	if (content.IsEnd()) {
		return memento.IsMask(false);
	}
	bool isMask = m_pattern == content.GetChar();
	content.Next();
	return memento.IsMask(isMask);
}