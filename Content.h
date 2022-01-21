#ifndef __CONTENT_H__
#define __CONTENT_H__
#include <vector>
#include <stack>
#include <string>
class Config;
class Pattern;
class Content {
public:
	class CursorsMemento {
	public:
		explicit CursorsMemento(Content &content, Pattern &pattern);
		~CursorsMemento();
		bool IsMatch(bool isMatch);
	private:
		friend class Content;
		Content &m_content;
		Pattern &m_pattern;
		bool m_is_match = false;
		size_t m_cursor = 0;
		size_t m_line_NO = 1;
	};
	explicit Content(const std::string fileName, const Config &config);
	void Load();
	void Parse();
	char GetChar();
	bool Previous();
	bool Next(const Pattern &pattern);
	bool IsEnd();
	void PushCursor();
	void PopCursor();
	std::string GetMemInfo(const Content::CursorsMemento &memento);
	bool NotForward() const;
	size_t GetLineNO()const;
	size_t GetCursor()const;
	
private:
	friend class CursorsMemento;
	const Config &m_config;
	const std::string m_file_name;
	std::vector<char> m_content;
	size_t m_cursor = 0;
	size_t m_line_NO = 1;
	size_t m_best_match_cursor = 0;
	size_t m_best_match_line_NO = 1;
	const Pattern *m_best_match_pattern = NULL;
};

#endif