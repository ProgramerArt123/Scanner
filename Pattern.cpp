#include "Content.h"
#include "Pattern.h"

Pattern::Pattern(uint64_t lineNO, uint64_t colNO) :
	m_line_NO(lineNO), m_col_NO(colNO){
}
Pattern::~Pattern() {
	
}
bool Pattern::IsMask(Content &content) {
	Content::CursorsMemento memento(content);
	uint64_t times = 0;
	while (times++ < m_max_times) {
		if (!IsMaskOnce(content)) {
			break;
		}
	}
	return memento.IsMask(times > m_min_times);
}
bool Pattern::IsMaskOnce(Content &content) {
	for (const std::shared_ptr<Pattern> &child : m_children) {
		if (!child->IsMask(content)) {
			return false;
		}
	}
	return true ;
}

void Pattern::AddChild(std::shared_ptr<Pattern> child) {
	m_children.push_back(child);
}

void Pattern::SetLastChildTimes(uint64_t minTimes, uint64_t maxTimes) {
	m_children.back()->m_min_times = minTimes;
	m_children.back()->m_max_times = maxTimes;
}
