#include <fstream>
#include <iostream>
#include "Pattern.h"
#include "Config.h"

Config::Config(const std::string fileName):
	m_file_name(fileName) {
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
			m_rules[label].reset(new Rule(*this, label, pattern, lineNO));
		}
		lineNO++;
	}
	
	if (m_rules.find("main") == m_rules.end()) {
	//	throw std::string("main rule not defined!");
	}
	
	for (auto &rule : m_rules) {
		rule.second->Parse();
	}
	
}

void Config::CheckDuplicate() {
	std::cout << "check pattern start......" << std::endl;
	for (std::map<std::string, std::unique_ptr<Rule>>::iterator rule =
		m_rules.begin(); rule != m_rules.end(); rule ++) {
		rule->second->Foreach(rule);
	}
	std::cout << "check pattern finish" << std::endl;
}

void Config::ParseContent(Content &content) const {
	
}

Rule &Config::GetRule(const std::string name) {
	if (m_rules.end() == m_rules.find(name)) {
		throw name + " undefined!";
	}
	return *m_rules[name];
}
void Config::CheckDuplicate(std::map<std::string, std::unique_ptr<Rule>>::iterator current,
	const Pattern &other) const {
		for (std::map<std::string, std::unique_ptr<Rule>>::iterator rule =
			++current; rule != m_rules.end(); rule++) {
		rule->second->CheckDuplicate(other);
	}
}