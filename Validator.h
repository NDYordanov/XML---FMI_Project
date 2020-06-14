#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <string>
#include "Structure.h"

class Validator {
public:
	static Structure getValidXMLStructureFromString(std::string content, std::string& error);
private:

	bool getValidPrologAttributes(int& n, Structure& xmls, std::string content, std::string& error);
	bool getValidElements(int& n, Structure& xmls, std::string content, std::string& error);

	bool getText(int& i, std::string& content, std::string& text);
	bool getStartOfTag(int& i, std::string& content);
	bool getEndOfTag(int& i, std::string& content);
	bool getTagName(int& i, std::string& content, std::string& key);
	bool getEndOfTagName(int& i, std::string& content);
	bool getAttribute(int& i, std::string& content, std::string& name, std::string& value);
	bool getEndOfQuote(int& i, std::string& content);
	bool getEndOfAttributeName(int& i, std::string& content);
	bool getEndOfProlog(int& i, std::string& content);
	void skipWhiteSpace(int& i, std::string& content);
	bool isWhiteSpace(char x);
};

#endif