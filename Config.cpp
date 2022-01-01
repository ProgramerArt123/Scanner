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
	std::string line;
	while (std::getline(config, line)) {
		if (!line.empty()) {
			const std::size_t pos = line.find_first_of(":");
			if (std::string::npos == pos) {
				throw "[" + line + "] is illegal rule!";
			}
			const std::string &label = line.substr(0, pos);
			if (m_rules.end() != m_rules.find(label)) {
				std::cout << label << " override!";
			}
			const std::string &pattern = line.substr(pos + 1);
			//std::cout << "label:" << label << ",pattern:" << pattern << std::endl;
			SetRule(label, new Rule(*this, label, pattern, lineNO));
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
	return *m_rules[name];
}

void Config::BindActionFunction(const std::string name, action func) {
	m_actions[name] = func;
}

bool Config::TryExecuteAction(const std::string name, const Lexical &lexical, const Content &content) const {
	bool isActionBind = IsActionBind(name);
	if (isActionBind) {
		ExecuteAction(name, lexical, content);
	}
	return isActionBind;
}

bool Config::IsActionBind(const std::string name) const {
	return m_actions.find(name) != m_actions.end();
}
void Config::ExecuteAction(const std::string name, const Lexical &lexical, const Content &content) const {
	m_actions.at(name)(lexical, content);
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