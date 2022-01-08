#ifndef __CONTENT_H__
#define __CONTENT_H__
#include <vector>
#include <stack>
#include <string>
class Config;
class Content {
public:
	explicit Content(const std::string fileName, const Config &config);
	void Load();
	void Parse();
	char GetChar();
	bool Previous();
	bool Next();
	bool IsEnd();
	void PushCursor();
	void PopCursor();
	
	class CursorsMemento {
	public:
		explicit CursorsMemento(Content &content);
		~CursorsMemento();
		bool IsMask(bool isMask);
	private:
		Content &m_content;
		bool m_is_mask = false;
	};
private:
	const Config &m_config;
	const std::string m_file_name;
	std::vector<char> m_content;
	size_t m_cursor = 0;
	std::stack<size_t> m_cursors_memento;
};

#endif