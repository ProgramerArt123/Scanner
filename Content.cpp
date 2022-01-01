#include <fstream>
#include <sstream>
#include <iostream>
#include "Config.h"
#include "Lexical.h"
#include "Content.h"

Content::CursorsMemento::CursorsMemento(Content &content, Pattern &pattern):
	m_content(content),m_pattern(pattern){
		m_line_NO = m_content.GetLineNO();
		m_real_end_cursor =  m_begin_cursor = m_content.GetCursor();
		m_pattern.SetMementoCursor(m_begin_cursor);
}
Content::CursorsMemento::~CursorsMemento() {
	m_pattern.SetMementoCursor(UINT64_MAX);
	if (!m_is_match) {
		m_content.m_cursor = m_begin_cursor;
		m_content.m_line_NO = m_line_NO;
	}
}

bool Content::CursorsMemento::IsMatch(bool isMatch) {
	return m_is_match = isMatch;
}

size_t Content::CursorsMemento::GetBeginCursor() {
	return m_begin_cursor;
}
void Content::CursorsMemento::MemRealEndCursor() {
	m_real_end_cursor = m_content.GetCursor();
}

size_t Content::CursorsMemento::GetRealEndCursor() {
	return m_real_end_cursor;
}
Content::Content(const std::string fileName, const Config &config):
	m_file_name(fileName), m_config(config),m_lexical(new Lexical(0, 0)){
}
Content::~Content() {
	
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
	if (m_content.empty()) {
		return true;
	}
	return m_cursor >= m_content.size() - 1;
}


std::string Content::GetMemInfo(const Content::CursorsMemento &memento) {
	size_t len = m_content.size() - memento.m_begin_cursor < 10 ?
		m_content.size() - memento.m_begin_cursor : 10;
	const std::string content(m_content.begin() + memento.m_begin_cursor,
		m_content.begin() + memento.m_begin_cursor + len);
	return "line:" + std::to_string(memento.m_line_NO) + 
		",cursor:" + std::to_string(memento.m_begin_cursor) +
		",content:" + content + "...";
}
bool Content::NotForward() const {
	return false; //TODO
}
size_t Content::GetLineNO()const {
	return m_line_NO;
}
size_t Content::GetCursor() const{
	return m_cursor;
}
Lexical &Content::GetLexicalRoot() {
	return *m_lexical;
}
const std::string Content::GetContent(size_t from, size_t to) const {
	if (from >= m_content.size() || to >= m_content.size()) {
		throw std::string("cursor overflow!");
	}
	const std::string content(m_content.begin() + from, 
		m_content.begin() + to);
	return content;
}
void Content::ForeachTryCommandAction() {
	m_lexical->ForeachTryCommandAction(*this);
}