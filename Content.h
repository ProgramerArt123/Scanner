#ifndef __CONTENT_H__
#define __CONTENT_H__
#include <vector>
#include <stack>
#include <string>
class Config;
class Pattern;
class Content {
public:
	explicit Content(const std::string fileName, const Config &config);
	void Load();
	void Parse();
	char GetChar();
	bool Previous();
	bool Next(const Pattern &pattern);
	bool IsEnd();
	void PushCursor();
	void PopCursor();
	std::string GetMemInfo();
	class CursorsMemento {
	public:
		explicit CursorsMemento(Content &content);
		~CursorsMemento();
		bool IsMatch(bool isMatch);
	private:
		Content &m_content;
		bool m_is_match = false;
	};
private:
	const Config &m_config;
	const std::string m_file_name;
	std::vector<char> m_content;
	size_t m_cursor = 0;
	size_t m_line_NO = 1;
	std::stack<std::pair<size_t, size_t>> m_cursors_memento;
	size_t m_best_match_cursor = 0;
	size_t m_best_match_line_NO = 1;
	const Pattern *m_best_match_pattern = NULL;
};

#endif