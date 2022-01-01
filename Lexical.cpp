#include "Pattern.h"
#include "Lexical.h"
Lexical::Lexical(const Pattern *pattern): m_pattern(pattern) {
	
}
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
const std::string &Lexical::GetContent() const {
	return m_content;
}
void Lexical::ForeachTopLeftRigth() {
	if (m_pattern) {
		m_pattern->TryCommandAction(*this);
	}
	for (auto child : m_children) {
		child->ForeachTopLeftRigth();
	}
}