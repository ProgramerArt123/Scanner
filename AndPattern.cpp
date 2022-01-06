#include "AndPattern.h"
AndPattern::~AndPattern() {}

bool AndPattern::IsMask(Content &content) {
	for (const std::unique_ptr<Pattern> &child : m_children) {
		if (!child->IsMask(content)) {
			return false;
		}
	}
	return true;
}