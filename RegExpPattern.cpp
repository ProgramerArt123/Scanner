#include "RegExpPattern.h"

RegExpPattern::RegExpPattern(const std::string pattern):
	m_pattern(pattern){}
RegExpPattern::~RegExpPattern() {}
bool RegExpPattern::IsMask(Content &content)  {
	return false;
}