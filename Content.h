#ifndef __CONTENT_H__
#define __CONTENT_H__
#include <vector>
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
private:
	const Config &m_config;
	const std::string m_file_name;
	std::vector<char> m_content;
	size_t m_cursor = 0;
};

#endif