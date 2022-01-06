#include "OrPattern.h"
OrPattern::~OrPattern() {}
	
bool OrPattern::IsMask(Content &content) {
	for (const std::unique_ptr<Pattern> &child : m_children) {
		if (child->IsMask(content)) {
			return true;
		}
	}
	return false;
}