#include <iostream>
#include "CodeGenerate.h"
#include "Rule.h"
#include "AndPattern.h"

AndPattern::AndPattern(Rule &rule, uint64_t lineNO, uint64_t colNO): 
	Pattern(rule, lineNO, colNO, PATTERN_TYPE_AND) {
		CodeGenerate::GetInstance().GetSourceStream() <<
		"\tstd::shared_ptr<Pattern> pattern"<< m_flag <<"(new AndPattern(*rule" << rule.GetFlag() <<", " << lineNO << ", " << colNO << "));"
		<< std::endl;
}