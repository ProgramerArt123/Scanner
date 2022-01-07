#include "Content.h"
#include "AndPattern.h"
AndPattern::~AndPattern() {}

bool AndPattern::IsMask(Content &content) {
	Content::CursorsMemento memento(content);
	for (const std::unique_ptr<Pattern> &child : m_children) {
		if (!child->IsMask(content)) {
			return memento.IsMask(false);
		}
	}
	return memento.IsMask(true) ;
}