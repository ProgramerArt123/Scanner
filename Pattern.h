#ifndef __PATTERN_H__
#define __PATTERN_H__
class Content;
class Pattern {
public:
	virtual ~Pattern();
	virtual bool IsMask(Content &content) = 0;
};

#endif