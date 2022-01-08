#include "Content.h"
#include "OrPattern.h"
OrPattern::~OrPattern() {}
	
bool OrPattern::IsMask(Content &content) {
	Content::CursorsMemento memento(content);
	for (const std::shared_ptr<Pattern> &child : m_children) {
		if (child->IsMask(content)) {
			return memento.IsMask(true);
		}
	}
	return memento.IsMask(false);
}