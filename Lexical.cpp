#include "Lexical.h"
void Lexical::InsertChild(std::shared_ptr<Lexical> &child, size_t pos) {
	if (UINT64_MAX == pos) {
		m_children.push_back(child);
	}
	else {
		m_children.insert(m_children.begin() + pos, child);
	}
}
size_t Lexical::GetChildrenCount() const {
	return m_children.size();
}
void Lexical::SetContent(const std::string content) {
	m_content = content;
}