#include <fstream>
#include <iostream>
#include "CodeGenerate.h"
CodeGenerate &CodeGenerate::GetInstance() {
	static CodeGenerate instance("Generate");
	return instance;
}
CodeGenerate::~CodeGenerate() {
	const std::string &headerFileName = m_file_name + ".h";
	OutPutFile(headerFileName, GetHeaderStream());
	const std::string &sourceFileName = m_file_name + ".cpp";
	OutPutFile(sourceFileName, GetSourceStream());
}
std::stringstream &CodeGenerate::GetHeaderStream() {
	return m_header_stream;
}
std::stringstream &CodeGenerate::GetSourceStream() {
	return m_source_stream;
}
CodeGenerate::CodeGenerate(const std::string fileName):
	m_file_name(fileName) {
		GetHeaderStream() << "#include <memory>" << std::endl ;
		GetHeaderStream() << "#include \"Config.h\"" << std::endl << std::endl;
		
		GetSourceStream() << "#include \"Pattern.h\"" << std::endl;
		GetSourceStream() << "#include \"AndPattern.h\"" << std::endl;
		GetSourceStream() << "#include \"OrPattern.h\"" << std::endl;
		GetSourceStream() << "#include \"CharPattern.h\"" << std::endl;
		GetSourceStream() << "#include \"StringPattern.h\"" << std::endl;
		GetSourceStream() << "#include \"" << m_file_name << ".h\"" << std::endl << std::endl;
}

void CodeGenerate::OutPutFile(const std::string &fileName, const std::stringstream &stream) {
	{
		std::ofstream out(fileName);
		if (!out.is_open()) {
			std::cerr << "Clear " << fileName << " Failed!" << std::endl;
		}
	}
	if (m_generate) {
		std::ofstream out(fileName);
		if (out.is_open()) {
			const std::string &content = stream.str();
#ifdef DEBUG
			std::cout << content;
#endif
			out << content;
			std::cout << "Output " << fileName << " success!" << std::endl;
		}
		else {
			std::cerr << "Output " << fileName << " Failed!" << std::endl;
		}
	}
}
void CodeGenerate::MarkGenerate() {
	m_generate = true;
}