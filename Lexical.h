#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include <memory>
#include <vector>
#include <string>
class Lexical {
public:
	void InsertChild(std::shared_ptr<Lexical> &child, size_t pos);
	size_t GetChildrenCount() const;
	void SetContent(const std::string content);
private:
	std::string m_content;
	std::vector<std::shared_ptr<Lexical>> m_children;
};

#endif