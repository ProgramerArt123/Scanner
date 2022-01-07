#include "Content.h"
#include "RepeatPattern.h"
RepeatPattern::RepeatPattern(uint64_t minTimes, uint64_t maxTimes):
	m_min_times(minTimes), m_max_times(maxTimes){
	
}
RepeatPattern::~RepeatPattern() {}
	
bool RepeatPattern::IsMask(Content &content) {
	Content::CursorsMemento memento(content);
	uint64_t times = 0;
	while (times ++ < m_max_times){
		if (!m_single->IsMask(content)) {
			break;
		}
	}
	return memento.IsMask(times > m_min_times);
}