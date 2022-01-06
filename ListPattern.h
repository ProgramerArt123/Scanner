#ifndef __LIST_PATTERN_H__
#define __LIST_PATTERN_H__

#include <list>
#include <memory>

#include "Pattern.h"
class ListPattern : public Pattern {
public:
	virtual ~ListPattern();
protected:
	std::list<std::unique_ptr<Pattern>> m_children;
};

#endif