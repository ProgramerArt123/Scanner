#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main(int argc, char *argv[]){
	try{
		const std::string configName = "c_front.s";
		std::ifstream config(configName);
		if (!config.is_open()){
			throw configName + " open failed!";
		}
		std::map<std::string, std::string> rules;
		std::string line;
		while (std::getline(config, line)) {
			if (!line.empty()) {
				const std::size_t pos = line.find_first_of(":");
				if (std::string::npos == pos) {
					throw "[" + line + "] is illegal rule!";
				}
				const std::string &label = line.substr(0, pos);
				if (rules.end() != rules.find(label)) {
					std::cout << label << " override!";
				}
				rules[label] = line.substr(pos + 1);
			}
		}
	}
	catch (const std::string &e){
		std::cerr << e;
	}
	
	return 0;
}