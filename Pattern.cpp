#include "Content.h"
#include "Pattern.h"
Pattern::~Pattern() {
	
}
bool Pattern::IsMask(Content &content) {
	Content::CursorsMemento memento(content);
	for (const std::shared_ptr<Pattern> &child : m_children) {
		if (!child->IsMask(content)) {
			return memento.IsMask(false);
		}
	}
	return memento.IsMask(true) ;
}