#include <iostream>
#include <string.h>
#include <memory>
#include "Lexical.h"
#include "Config.h"
#include "Content.h"

void ProcDef(const Lexical &lexical, const Content &content) {
	std::cout << "ProcDef:" << lexical.GetContent() << std::endl;
}

int main(int argc, char *argv[]){
	try{
		std::string configFileName = "c_front.s";
		if (argc > 1) {
			configFileName = argv[1];
		}
		Config config(configFileName);
		config.Parse();
#ifdef DEBUG
		//config.CheckDuplicate();
		Content content("test.p", config);
		content.Load();
		content.Parse();
		config.BindActionFunction("ProcDef", &ProcDef);
		content.ForeachLexical();
#endif
	}
	catch (const std::string &e){
		std::cerr << e;
	}
	
	return 0;
}