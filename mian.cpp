#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//using namespace std;
#include "StackString.h"
#include "Attribute.h"
#include "Element.h"
#include "Structure.h"
#include "Validator.h"
#include "Reader.h"
#include "Path.h"
#include "Parser.h"

int main() {

	Parser parser;
	parser.commandLineInteface();

	return 0;
}