#ifndef READER_H
#define READER_H
#include <string>
#include <fstream>
class Reader
{
public:
	std::string readFile(std::string path);
	std::string writeFile(std::string path, std::string data);
private:
	std::ifstream input;
	std::ofstream output;
};

#endif

