#include <iostream>
#include <string.h>
#include <memory>
#include "Config.h"
#include "Content.h"

int main(int argc, char *argv[]){
	try{
		Config config("c_front.s");
		config.Parse();
		//config.CheckDuplicate();
		Content content("test.p", config);
		content.Load();
		content.Parse();
	}
	catch (const std::string &e){
		std::cerr << e;
	}
	
	return 0;
}