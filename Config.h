#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <map>
#include <memory>

#include "Rule.h"

class Content;
class Config {
public:
	explicit Config(const std::string fileName);
	void Parse();
	void CheckRepeat();	
	void ParseContent(Content &content) const;
private:
	const std::string m_file_name;
	std::map<std::string, std::shared_ptr<Rule>> m_rules;
};

#endif