#include "Config.h"
#include "Content.h"

Content::CursorsMemento::CursorsMemento(Content &content) :
	m_content(content){
		m_content.PushCursor();
}
Content::CursorsMemento::~CursorsMemento() {
	if (!m_is_match) {
		m_content.PopCursor();
	}
}

bool Content::CursorsMemento::IsMatch(bool isMatch) {
	return m_is_match = isMatch;
}

Content::Content(const std::string fileName, const Config &config):
	m_file_name(fileName), m_config(config){
	
}
void Content::Load() {}
void Content::Parse() {
	m_config.ParseContent(*this);
}
char Content::GetChar() {
	if (m_cursor >= m_content.size()) {
		throw std::string("cursor overflow!");
	}
	return m_content[m_cursor];
}
bool Content::Previous() {
	if (0 == m_cursor) {
		return false;
	}
	else {
		m_cursor--;
		return true;
	}
}
bool Content::Next() {
	if (m_content.empty()) {
		return false;
	}
	if (m_cursor < m_content.size() - 1) {
		m_cursor++;
		return true;
	}
	else {
		return false;
	}
}
bool Content::IsEnd() {
	return m_cursor < m_content.size();
}

void Content::PushCursor() {
	m_cursors_memento.push(m_cursor);
}
void Content::PopCursor() {
	if (m_cursors_memento.empty()) {
		throw std::string("cursor stack unbalance!");
	}
	m_cursor = m_cursors_memento.top();
	m_cursors_memento.pop();
}