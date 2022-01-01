#include <fstream>
#include <iostream>
#include "Pattern.h"
#include "Content.h"
#include "CodeGenerate.h"
#include "Config.h"

Config::Config(const std::string fileName):
	m_file_name(fileName) {
		static uint64_t flag = 0;
		m_flag = flag++;
		CodeGenerate::GetInstance().GetHeaderStream() <<
		"std::shared_ptr<Config> GenerateConfig" << m_flag << "();" << std::endl;
		CodeGenerate::GetInstance().GetSourceStream() <<
		"std::shared_ptr<Config> GenerateConfig" << m_flag << "(){" << std::endl <<
		"\tstd::shared_ptr<Config> config" << m_flag << "(new Config(\"" << fileName << "\"));"
		<< std::endl;
}
Config::~Config() {
	CodeGenerate::GetInstance().GetSourceStream() << "\treturn config" << m_flag << ";" << std::endl << "}" << std::endl;
}
void Config::Parse() {
	std::ifstream config(m_file_name);
	if (!config.is_open()) {
		throw m_file_name + " open failed!";
	}
	
	uint64_t lineNO = 1;
	std::stringstream ruleStream;
	std::string line;
	while (std::getline(config, line)) {
		ruleStream << line;
		if (line.empty() || config.eof()) {
			const std::string &cleanString = CleanRule(ruleStream.str());
			if (!cleanString.empty()) {
				const std::size_t pos = cleanString.find_first_of(":");
				if (std::string::npos == pos) {
					throw "[" + cleanString + "] is illegal rule!";
				}
				std::string label = cleanString.substr(0, pos);
				bool isSegmentation = CheckSegmentation(label);
				bool isTerminate = CheckTerminate(label);
				if (m_rules.end() != m_rules.find(label)) {
					std::cout << label << " override!";
				}
				const std::string &pattern = cleanString.substr(pos + 1);
				//std::cout << "label:" << label << ",pattern:" << pattern << std::endl;
				SetRule(label, new Rule(*this, label, pattern, lineNO, isSegmentation, isTerminate));
				ruleStream.str("");
			}
		}
		lineNO++;
	}
	
	if (m_rules.find("main") == m_rules.end()) {
		throw std::string("main rule not defined!");
	}
	
	for (auto &rule : m_rules) {
		rule.second->Parse();
	}
	
	CodeGenerate::GetInstance().MarkGenerate();
}

void Config::CheckDuplicate() {
	std::cout << "check pattern start......" << std::endl;
	for (std::map<std::string, std::unique_ptr<Rule>>::iterator i =
		m_rules.begin(); i != m_rules.end(); i ++) {
			for (std::map<std::string, std::unique_ptr<Rule>>::iterator j = 
				i; j != m_rules.end(); j++) {
				i->second->CheckDuplicate(*j->second);
		}
	}
	std::cout << "check pattern finish" << std::endl;
}

bool Config::ParseContent(Content &content) const {
	if (m_rules.find("main") == m_rules.end()) {
		throw std::string("main rule not defined!");
	}
	while (!content.IsEnd()) {
		if (!m_rules.at("main")->IsMatch(content)) {
			return false;
		}
	}
	return true;
}

Rule &Config::GetRule(const std::string name) {
	if (m_rules.end() == m_rules.find(name)) {
		throw name + " undefined!";
	}
	return *m_rules.at(name);
}

void Config::BindActionFunction(const std::string name, action enter, action exit) {
	m_actions[name].first = enter;
	m_actions[name].second = exit;
}

bool Config::TryExecuteActionEnter(const std::string name, const Lexical &lexical, Content &content) const {
	bool isActionBind = IsActionBind(name);
	if (isActionBind) {
		ExecuteActionEnter(name, lexical, content);
	}
	return isActionBind;
}

bool Config::TryExecuteActionExit(const std::string name, const Lexical &lexical, Content &content) const {
	bool isActionBind = IsActionBind(name) && m_actions.at(name).second;
	if (isActionBind) {
		ExecuteActionExit(name, lexical, content);
	}
	return isActionBind;
}

bool Config::IsActionBind(const std::string name) const {
	return m_actions.find(name) != m_actions.end();
}
void Config::ExecuteActionEnter(const std::string name, const Lexical &lexical,  Content &content) const {
	m_actions.at(name).first(lexical, content);
}
void Config::ExecuteActionExit(const std::string name, const Lexical &lexical, Content &content) const {
	m_actions.at(name).second(lexical, content);
}

uint64_t Config::GetFlag() const {
	return m_flag;
}

void Config::SetRule(const std::string name, Rule *rule) {
	m_rules[name].reset(rule);
	CodeGenerate::GetInstance().GetSourceStream() <<
	"\tconfig" << m_flag << "->SetRule(\"" << name << "\",rule" << rule->GetFlag() << ");"
	<< std::endl;
}

bool Config::IsHaveIgnore() const {
	return m_rules.find(IGNORE) != m_rules.end();
}
Pattern &Config::GetIgnore() {
	return *GetRule(IGNORE).GetPattern();
}
const std::string Config::CleanRule(const std::string &rule) {
	std::unique_ptr<char[]> cleanRule(new char[rule.length() + 1]());
	size_t index = 0, cleanIndex = 0;
	while (index < rule.length()) {
		if (rule[index] == ' ' || rule[index] == '\t' ||
			rule[index] == '\r' || rule[index] == '\n') {
			index++;
		}
		else {
			cleanRule[cleanIndex++] = rule[index++];
		}
	}
	return cleanRule.get();
}
bool Config::CheckSegmentation(std::string &name) {
	const std::string head = IGNORE;
	bool isSegmentation = name != IGNORE && 
		 name.length() > head.size() &&
		0 == name.compare(0, head.length(), head);
	if (isSegmentation) {
		name = name.substr(head.length());
	}
	return isSegmentation;
}

bool Config::CheckTerminate(std::string &name) {
	const std::string tail = TERMINATE;
	bool isTerminate = name.length() > tail.length() &&
		0 == name.compare(name.length() - tail.length(),
		tail.length(), tail);
	if (isTerminate) {
		name = name.substr(0, name.length() - tail.length());
	}
	return isTerminate;
}