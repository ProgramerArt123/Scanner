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
	void CheckDuplicate();	
	bool ParseContent(Content &content) const;
	Rule &GetRule(const std::string name);

	
	std::map<std::string, std::unique_ptr<Rule>>::iterator
		begin() {return m_rules.begin();}
	std::map<std::string, std::unique_ptr<Rule>>::iterator
		end() {return m_rules.end();}
private:
	const std::string m_file_name;
	std::map<std::string, std::unique_ptr<Rule>> m_rules;
};

#endif