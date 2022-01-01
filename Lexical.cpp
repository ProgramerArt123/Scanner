#include "Pattern.h"
#include "Lexical.h"
Lexical::Lexical(uint64_t lineNO, uint64_t colNO, const Pattern *pattern): 
	m_line_NO(lineNO), m_col_NO(colNO), m_pattern(pattern) {
	
}
void Lexical::InsertChild(std::shared_ptr<Lexical> &child, size_t pos) {
	if (UINT64_MAX == pos) {
		m_children.push_back(child);
	}
	else {
		m_children.insert(m_children.begin() + pos, child);
	}
}

void Lexical::SetContent(const std::string content) {
	m_content = content;
}
const std::string &Lexical::GetContent() const {
	return m_content;
}
void Lexical::ForeachTryCommandAction(Content &content) {
	if (m_pattern) {
		m_pattern->TryCommandActionEnter(*this, content);
	}
	for (auto child : m_children) {
		child->ForeachTryCommandAction(content);
	}
	if (m_pattern) {
		m_pattern->TryCommandActionExit(*this, content);
	}
}
bool Lexical::ForeachTopLeftRigthInterrupt(std::function<bool(const Lexical &)> factor) const{
	if (factor(*this)) {
		return true;
	}
	for (auto child : m_children) {
		if (child->ForeachTopLeftRigthInterrupt(factor)) {
			return true;
		}
	}
	return false;
}
void Lexical::SetParent(const Lexical *parent) {
	m_parent = parent;
}

bool Lexical::IsRoot() const {
	return NULL == m_parent;
}
const Pattern &Lexical::GetPattern() const {
	return *m_pattern;
}
size_t Lexical::GetChildrenCount() const {
	return m_children.size();
}
size_t Lexical::GetBrotherCount() const {
	if (IsRoot()) {
		throw std::string("Lexical is Root!");
	}
	return m_parent->GetChildrenCount();
}
const std::shared_ptr<Lexical> &Lexical::GetChild(size_t index) const {
	if (GetChildrenCount() <= index) {
		throw std::string("Lexical Child count overflow!");
	}
	return m_children[index];
}
const std::shared_ptr<Lexical> &Lexical::GetBrother(size_t index) const {
	if (IsRoot()) {
		throw std::string("Lexical is Root!");
	}
	return m_parent->GetChild(index);
}
uint64_t Lexical::GetLineNO() const {
	return m_line_NO;
}
uint64_t Lexical::GetColNO() const {
	return m_col_NO;
}
void Lexical::Error(const std::string &info) const throw (std::string) {
	throw "Lexical_Error=>line:【"  + std::to_string(m_line_NO) + 
		"】, content 【" + GetContent() + "】 " + info;
}