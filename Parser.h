#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "Structure.h"
#include "Reader.h"

class Parser {
public:
	// void commandLineInteface(istream in, ostream out);
	void commandLineInteface();
private:

	bool exitCommand();
	bool openCommand();
	bool newCommand();
	bool closeCommand();
	bool saveCommand();
	bool saveAsCommand();
	bool printCommand();
	bool getCommand();
	bool setCommand();
	bool addCommand();
	bool removeCommand();
	bool XPathCommand();
	bool helpCommand();
	bool notFoundCommand(std::string);

	std::string file;
	Structure structure;
	Reader reader;
};

#endif