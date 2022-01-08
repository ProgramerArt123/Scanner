#include "Content.h"
#include "OrPattern.h"
OrPattern::OrPattern(uint64_t lineNO, uint64_t colNO):
	Pattern(lineNO, colNO){
	
}
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