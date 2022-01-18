#include <fstream>
#include <sstream>
#include <iostream>
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
void Content::Load() {
	std::ifstream file(m_file_name);
	if (!file.is_open()) {
		throw m_file_name + " open failed!";
	}
	std::stringstream buffer;  
	buffer << file.rdbuf();
	const std::string &content = buffer.str();
	m_content.assign(content.begin(), content.end());
}
void Content::Parse() {
	if (!m_config.ParseContent(*this)) {
		if (m_best_match_pattern) {
			std::cout << std::endl;
			std::cout << "The best match trace:" << std::endl;
			std::cout << "The best match cursor:" << m_best_match_cursor << 
				",line:" << m_best_match_line_NO << ",near:\"";
			size_t from = m_best_match_cursor - 5 >= 0 ? m_best_match_cursor - 5 : 0;
			size_t to = m_best_match_cursor + 5 <= m_content.size() ? m_best_match_cursor + 5 : m_content.size();
			for (size_t index = from; index < to; index ++) {
				if (index == m_best_match_cursor) {
					std::cout << "'";
				}
				std::cout << m_content[index];
				if (index == m_best_match_cursor) {
					std::cout << "'";
				}
			}
			std::cout << "\"" << std::endl;
			m_best_match_pattern->BestMatchTracePrint();
			std::cout << std::endl;
		}
		throw m_file_name + " parse failed!";
	}
	else {
		std::cout << m_file_name + " parse success!" <<std::endl;
	}
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
bool Content::Next(const Pattern &pattern) {
	if (m_content.empty()) {
		return false;
	}
	if (m_cursor < m_content.size() - 1) {
		if (m_content.at(m_cursor) == '\n') {
			m_line_NO++;
		}
		m_cursor++;
		if (m_cursor > m_best_match_cursor) {
			m_best_match_cursor = m_cursor;
			m_best_match_line_NO = m_line_NO;
			m_best_match_pattern = &pattern;
		}
		return true;
	}
	else {
		return false;
	}
}
bool Content::IsEnd() {
	return m_cursor >= m_content.size();
}

void Content::PushCursor() {
	m_cursors_memento.push(std::pair<size_t, size_t>(m_cursor, m_line_NO));
}
void Content::PopCursor() {
	if (m_cursors_memento.empty()) {
		throw std::string("cursor stack unbalance!");
	}
	m_cursor = m_cursors_memento.top().first;
	m_line_NO = m_cursors_memento.top().second;
	m_cursors_memento.pop();
}
std::string Content::GetMemInfo() {
	if (m_cursors_memento.empty()) {
		throw std::string("Content::GetMemInfo No Mem!");
	}
	size_t len = m_content.size() - m_cursors_memento.top().first < 10 ?
		m_content.size() - m_cursors_memento.top().first : 10;
	const std::string content(m_content.begin() + m_cursors_memento.top().first,
		m_content.begin() + m_cursors_memento.top().first + len);
	return "line:" + std::to_string(m_cursors_memento.top().second) + 
		",cursor:" + std::to_string(m_cursors_memento.top().first) +
		",content:" + content + "...";
}
bool Content::NotForward() const {
	if (m_cursors_memento.empty()) {
		return true;
	}
	return m_cursors_memento.top().first 
		== m_cursor;
}
size_t Content::GetLineNO() {
	return m_line_NO;
}
size_t Content::GetCursor() {
	return m_cursor;
}