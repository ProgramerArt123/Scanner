#include <fstream>
#include <iostream>
#include "CodeGenerate.h"
CodeGenerate &CodeGenerate::GetInstance() {
	static CodeGenerate instance("Generate.h");
	return instance;
}
CodeGenerate::~CodeGenerate() {
	{
		std::ofstream out(m_file_name);
		if (!out.is_open()) {
			std::cerr << "Clear " << m_file_name << " Failed!" << std::endl;
		}
	}
	if (m_generate) {
		std::ofstream out(m_file_name);
		if (out.is_open()) {
			out << m_stream.str();
		}
		else {
			std::cerr << "Output " << m_file_name << " Failed!" << std::endl;
		}
	}
}
std::stringstream &CodeGenerate::GetStream() {
	return m_stream;
}
CodeGenerate::CodeGenerate(const std::string fileName):
	m_file_name(fileName) {
}
void CodeGenerate::MarkGenerate() {
	m_generate = true;
}