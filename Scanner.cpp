#include <iostream>
#include <string.h>
#include <memory>
#include "Lexical.h"
#include "Config.h"
#include "Content.h"

void ProcDef(const Lexical &lexical) {
	std::cout << "ProcDef:" << lexical.GetContent() << std::endl;
}

int main(int argc, char *argv[]){
	try{
		Config config("c_front.s");
		config.Parse();
		//config.CheckDuplicate();
		Content content("test.p", config);
		content.Load();
		content.Parse();
		config.BindActionFunction("ProcDef", &ProcDef);
		content.ForeachLexical();
	}
	catch (const std::string &e){
		std::cerr << e;
	}
	
	return 0;
}