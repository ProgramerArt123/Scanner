#include <iostream>
#include "CodeGenerate.h"
#include "AndPattern.h"

AndPattern::AndPattern(Rule &rule, uint64_t lineNO, uint64_t colNO): 
	Pattern(rule, lineNO, colNO, PATTERN_TYPE_AND) {
		std::cout << "std::shared_ptr<Pattern> pattern" << m_flag << "(new AndPattern(rule, " << lineNO << ", " << colNO << "));" << std::endl;
		CodeGenerate::GetInstance().GetStream() <<
		"std::shared_ptr<Pattern> pattern"<< m_flag <<"(new AndPattern(rule, " << lineNO << ", " << colNO << "));"
		<< std::endl;
}