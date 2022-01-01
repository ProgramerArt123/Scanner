#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include <memory>
#include <vector>
#include <string>
class Pattern;
class Lexical {
public:
	explicit Lexical(const Pattern *pattern = NULL);
	void InsertChild(std::shared_ptr<Lexical> &child, size_t pos);
	size_t GetChildrenCount() const;
	void SetContent(const std::string content);
	const std::string &GetContent() const;
	void ForeachTopLeftRigth();
private:
	std::string m_content;
	std::vector<std::shared_ptr<Lexical>> m_children;
	const Pattern *m_pattern = NULL;
};

#endif