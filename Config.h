#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <map>
#include <memory>
#include <functional>

#include "Rule.h"

class Content;
class Lexical;
typedef void(*action)(const Lexical &lexical);
class Config {
public:
	explicit Config(const std::string fileName);
	void Parse();
	void CheckDuplicate();	
	bool ParseContent(Content &content) const;
	Rule &GetRule(const std::string name);
	void BindActionFunction(const std::string name, action func);	
	
	bool TryExecuteAction(const std::string name, const Lexical &lexical) const;
	
	std::map<std::string, std::unique_ptr<Rule>>::iterator
		begin() {return m_rules.begin();}
	std::map<std::string, std::unique_ptr<Rule>>::iterator
		end() {return m_rules.end();}
private:
	
	bool IsActionBind(const std::string name) const;
	void ExecuteAction(const std::string name, const Lexical &lexical) const;
	const std::string m_file_name;
	std::map<std::string, std::unique_ptr<Rule>> m_rules;
	std::map<std::string, std::function<void(const Lexical &)>> m_actions;
};

#endif