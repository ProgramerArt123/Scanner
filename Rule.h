#ifndef __RULE_H__
#define __RULE_H__

#include <string>
#include <vector>
#include <list>
#include <memory>

#include "Pattern.h"

class Config;
class CharPattern;
class Rule {
public:
	explicit Rule(Config &config, const std::string name, const std::string literal, uint64_t lineNO, bool isSegmentation, bool isTerminate);
	void Parse();
	void CheckDuplicate(const Rule &other);
	std::shared_ptr<Pattern> &GetPattern();
	Config &GetConfig();
	bool IsMatch(Content &content) const;
	const std::string &GetName();
	uint64_t GetFlag() const;
	void SetPattern(const std::shared_ptr<Pattern> &pattern);
	bool IsIgnore() const;
	bool IsSegmentation() const;
	bool IsTerminate() const;
private:
	void StringParse(Pattern &parent);
	void LabelParse(Pattern &parent);
	void RoundParse(Pattern &parent);
	void SquareParse(Pattern &parent);
	void CharParse(Pattern &parent, bool isEscape, bool isExclude);
	void Parse(Pattern &parent);
	void TryRangeParse(CharPattern &character);
	void TryActionParse(Pattern &round);
private:
	const std::vector<char> m_literal;
	std::shared_ptr<Pattern> m_pattern;
	Config &m_config;
	size_t m_index = 0;
	const uint64_t m_line_NO = 0;
	std::string m_name;
	uint64_t m_flag = 0;
	bool m_is_segmentation = false;
	bool m_is_terminate = false;
};

#endif