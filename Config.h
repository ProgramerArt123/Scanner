#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <map>
#include <memory>
#include <functional>

#include "Rule.h"

class Content;
class Lexical;
typedef void(*action)(const Lexical &lexical,  Content &content);
class Config {
public:
	explicit Config(const std::string fileName);
	~Config();
	void Parse();
	void CheckDuplicate();	
	bool ParseContent(Content &content) const;
	Rule &GetRule(const std::string name);
	void BindActionFunction(const std::string name, action enter, action exit = NULL);	
	
	bool TryExecuteActionEnter(const std::string name, const Lexical &lexical,  Content &content) const;
	bool TryExecuteActionExit(const std::string name, const Lexical &lexical, Content &content) const;
	uint64_t GetFlag() const;
	
	void SetRule(const std::string name, Rule *rule);
	
	std::map<std::string, std::unique_ptr<Rule>>::iterator
		begin() {return m_rules.begin();}
	std::map<std::string, std::unique_ptr<Rule>>::iterator
		end() {return m_rules.end();}
private:
	
	bool IsActionBind(const std::string name) const;
	void ExecuteActionEnter(const std::string name, const Lexical &lexical, Content &content) const;
	void ExecuteActionExit(const std::string name, const Lexical &lexical, Content &content) const;
	const std::string m_file_name;
	std::map<std::string, std::unique_ptr<Rule>> m_rules;
	std::map<std::string, std::pair<std::function<void(const Lexical &, Content &)>, std::function<void(const Lexical &, Content &)>>> m_actions;
	uint64_t m_flag = 0;
};

#endif