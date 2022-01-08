#include "Content.h"
#include "Pattern.h"

Pattern::Pattern(uint64_t lineNO, uint64_t colNO) :
	m_line_NO(lineNO), m_col_NO(colNO){
}
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

void Pattern::AddChild(std::shared_ptr<Pattern> child) {
	m_children.push_back(child);
}

void Pattern::ReplaceLastChild(std::shared_ptr<Pattern> newChild) {
	newChild->m_children.push_back(m_children.back());
	m_children.pop_back();
	m_children.push_back(newChild);
}