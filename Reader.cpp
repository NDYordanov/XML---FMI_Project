#include "Reader.h"
#include <string>
#include <fstream>
#include <vector>
//using namespace std;

std::string Reader::readFile(std::string path) {
	input.open(path.c_str());

	if (input.is_open()) {
		std::string line;
		std::getline(input, line, '\0');
		input.close();
		return line;
	}

	input.close();
	return "ERROR";
}

std::string Reader::writeFile(std::string path, std::string data) {
	output.open(path.c_str());

	if (output.is_open()) {
		output << data;
		output.close();
		return "VALID";
	}

	output.close();
	return "ERROR";
}