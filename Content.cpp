#include "Config.h"
#include "Content.h"

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