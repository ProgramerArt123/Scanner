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
	
	std::list<std::shared_ptr<Pattern>> m_children;
};

#endif