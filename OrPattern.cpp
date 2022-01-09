#include "Content.h"
#include "OrPattern.h"
OrPattern::OrPattern(uint64_t lineNO, uint64_t colNO):
	Pattern(lineNO, colNO){
	
}
OrPattern::~OrPattern() {}
	
bool OrPattern::IsMatchOnce(Content &content) {
	for (const std::shared_ptr<Pattern> &child : m_children) {
		if (child->IsMatch(content)) {
			return true;
		}
	}
	return false;
}