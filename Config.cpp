#include <fstream>
#include <iostream>
#include "Config.h"

Config::Config(const std::string fileName):
	m_file_name(fileName) {
}
void Config::Parse() {
	std::ifstream config(m_file_name);
	if (!config.is_open()) {
		throw m_file_name + " open failed!";
	}
	
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
			m_rules[label].reset(new Rule(*this, line.substr(pos + 1)));
		}
	}
	
	if (m_rules.find("main") == m_rules.end()) {
		throw std::string("main rule not defined!");
	}
	
	for (auto &rule : m_rules) {
		rule.second->Parse();
	}
	
}

void Config::CheckRepeat() {
	
}

void Config::ParseContent(Content &content) const {
	
}

Rule &Config::GetRule(const std::string name) {
	if (m_rules.end() == m_rules.find(name)) {
		throw name + " undefined!";
	}
	return *m_rules[name];
}