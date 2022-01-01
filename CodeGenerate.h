#ifndef __CODE_GENERATE_H__
#define __CODE_GENERATE_H__

#include <sstream>
#include <string>

class CodeGenerate {
public:
	static CodeGenerate &GetInstance();
	~CodeGenerate();
	std::stringstream &GetStream();
	void MarkGenerate();
private:
	explicit CodeGenerate(const std::string fileName);
	std::string m_file_name;
	std::stringstream m_stream;
	bool m_generate = false;
};

#endif