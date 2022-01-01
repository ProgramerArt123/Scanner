#include <iostream>
#include "CodeGenerate.h"
#include "AndPattern.h"

AndPattern::AndPattern(Rule &rule, uint64_t lineNO, uint64_t colNO): 
	Pattern(rule, lineNO, colNO, PATTERN_TYPE_AND) {
		CodeGenerate::GetInstance().GetStream() <<
		"\tstd::shared_ptr<Pattern> pattern"<< m_flag <<"(new AndPattern(rule, " << lineNO << ", " << colNO << "));"
		<< std::endl;
}