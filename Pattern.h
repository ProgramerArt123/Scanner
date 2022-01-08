#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <list>
#include <memory>
#include <stdint.h>
class Content;
class Pattern {
public:
	virtual ~Pattern();
	virtual bool IsMask(Content &content);
	void AddChild(std::shared_ptr<Pattern> child);
	void ReplaceLastChild(std::shared_ptr<Pattern> newChild);
protected:
	std::list<std::shared_ptr<Pattern>> m_children;
};

#endif