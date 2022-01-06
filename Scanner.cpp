#include <iostream>

#include "Config.h"
#include "Content.h"

int main(int argc, char *argv[]){
	try{
		Config config("c_front.s");
		config.Parse();
		config.CheckRepeat();
		Content content("test.p", config);
		content.Load();
		content.Parse();
	}
	catch (const std::string &e){
		std::cerr << e;
	}
	
	return 0;
}