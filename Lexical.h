#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include <memory>
#include <vector>
#include <string>
class Pattern;
class Content;
class Lexical {
public:
	explicit Lexical(uint64_t lineNO, uint64_t colNO, const Pattern *pattern = NULL);
	void InsertChild(std::shared_ptr<Lexical> &child, size_t pos);
	void SetContent(const std::string content);
	const std::string &GetContent() const;
	void SetParent(const Lexical *parent);
	void ForeachTryCommandAction(Content &content);
	bool ForeachTopLeftRigthInterrupt(std::function<bool(const Lexical &)> factor) const;
	uint64_t GetLineNO() const;
	uint64_t GetColNO() const;
	bool IsRoot() const;
	size_t GetChildrenCount() const;
	size_t GetBrotherCount() const;
	const std::shared_ptr<Lexical> &GetChild(size_t index) const;
	const std::shared_ptr<Lexical> &GetBrother(size_t index) const;
private:
	std::string m_content;
	
	std::vector<std::shared_ptr<Lexical>> m_children;
	const Pattern *m_pattern = NULL;
	const Lexical *m_parent = NULL;
	const uint64_t m_line_NO = 0;
	const uint64_t m_col_NO = 0;
};

#endif