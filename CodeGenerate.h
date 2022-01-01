#ifndef __CODE_GENERATE_H__
#define __CODE_GENERATE_H__

#include <sstream>
#include <string>

class CodeGenerate {
public:
	static CodeGenerate &GetInstance();
	~CodeGenerate();
	std::stringstream &GetHeaderStream();
	std::stringstream &GetSourceStream();
	void MarkGenerate();
private:
	explicit CodeGenerate(const std::string fileName);
	void OutPutFile(const std::string &fileName, const std::stringstream &stream);
	std::string m_file_name;
	std::stringstream m_header_stream;
	std::stringstream m_source_stream;
	bool m_generate = false;
};

#endif