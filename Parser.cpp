#include "Parser.h"
#include "Attribute.h"
#include "Element.h"
#include "Validator.h"
#include "Path.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void Parser::commandLineInteface() {
	std::cout << "XMLParser" << std::endl;

	this->file = "";

	std::string command;

	while (1) {
		if (this->file == "") {
			std::cout << '>';
		}
		else {
			std::cout << '(' << this->file << ')' << '>';
		}
		std::cin >> command;

		if (command == "forceexit") return;
		else if (command == "exit")
			if (!this->exitCommand()) return;
		else if (command == "open") 
			if (!this->openCommand()) return;
		else if (command == "new") 
			if (!this->newCommand()) return;
		else if (command == "print") 
			if (!this->printCommand()) return;
		else if (command == "close") 
			if (!this->closeCommand()) return;
		else if (command == "save") 
			if (!this->saveCommand()) return;
		else if (command == "saveAs") 
			if (!this->saveAsCommand()) return;
		else if (command == "get") 
			if (!this->getCommand()) return;
		else if (command == "set") 
			if (!this->setCommand()) return;
		else if (command == "add") 
			if (!this->addCommand()) return;
		else if (command == "remove") 
			if (!this->removeCommand()) return;
		else if (command == "XPath") 
			if (!this->XPathCommand()) return;
		else if (command == "help") 
			if (!this->helpCommand()) return;
		else if 
			(!this->notFoundCommand(command)) return;
	}
}

bool Parser::exitCommand() {

	std::string errormsg;
	char c;

	if (file == "")
		return false;

	else {
		std::cout << "Do you want to save your changes [y/n]: ";
		std::cin >> c;
		if (c == 'y') {
			errormsg = reader.writeFile(file, structure.toString());
			if (errormsg != "VALID") {
				std::cout << "Error saving file.";
				return true;
			}
			std::cout << "File saved.";
		}
		std::cout << "File \'" << file << "\' closed." << std::endl;
		file = "";
		return false;
	}
	return true;
}
bool Parser::openCommand() {

	std::string path, content, errormsg;

	if (file == "") {
		std::cout << "Open file [path/name]: ";
		std::cin >> path;
		content = reader.readFile(path);
		if (content == "ERROR") {
			std::cout << "Error opening file \'" << path << "\'." << std::endl;
			return true;
		}
		structure = Validator::getValidXMLStructureFromString(content, errormsg);
		if (errormsg != "VALID") {
			std::cout << "Error: file \'" << path << "\' is not valid. (" << errormsg << ")" << std::endl;
			return true;
		}
		file = path;
	}
	else {
		std::cout << "You are working on file \'" << file << "\'." << std::endl;
		std::cout << "Try \'close\' to close your current file." << std::endl;
	}
	return true;
}
bool Parser::newCommand() {

	std::string path, content;
	char c;

	if (file == "") {
		std::cout << "New file [path/name]> ";
		std::cin >> path;
		std::cout << "input: Root tag key> ";
		std::cin >> content;
		structure = Structure(content);
		file = path;
	}
	else {
		std::cout << "You are working on file \'" << file << "\'." << std::endl;
		std::cout << "Try \'close\' to close your current file." << std::endl;
	}
	return true;
}
bool Parser::closeCommand() {

	std::string errormsg;
	char c;

	if (file == "") {
		std::cout << "You are not working on any file." << std::endl;
		std::cout << "Try \'open\' or \'new\' to open/create file." << std::endl;
	}
	else {
		std::cout << "Do you want to save your changes [y/n]: ";
		std::cin >> c;
		if (c == 'y') {
			errormsg = reader.writeFile(file, structure.toString());
			if (errormsg != "VALID") {
				std::cout << "Error saving file.";
				return true;
			}
			std::cout << "File saved.";
		}
		std::cout << "File \'" << file << "\' closed." << std::endl;
		file = "";
	}
	return true;
}
bool Parser::saveCommand() {

	std::string errormsg;
	char c;

	if (file == "") {
		std::cout << "You are not working on any file." << std::endl;
		std::cout << "Try \'open\' or \'new\' to open/create file." << std::endl;
	}
	else {
		errormsg = reader.writeFile(file, structure.toString());
		if (errormsg != "VALID") {
			std::cout << "Error saving file.";
			return true;
		}
		std::cout << "File saved." << std::endl;
	}
	return true;
}
bool Parser::saveAsCommand() {

	std::string path, errormsg;

	if (file == "") {
		std::cout << "You are not working on any file." << std::endl;
		std::cout << "Try \'open\' or \'new\' to open/create file." << std::endl;
	}
	else {
		std::cout << "Save to [path/name]> ";
		std::cin >> path;
		errormsg = reader.writeFile(path, structure.toString());
		if (errormsg != "VALID") {
			std::cout << "Error saving file.";
			return true;
		}
		std::cout << "File saved." << std::endl;
		file = path;
	}
	return true;
}
bool Parser::printCommand() {
	if (file == "") {
		std::cout << "You are not working on any file." << std::endl;
		std::cout << "Try \'open\' or \'new\' to open/create file." << std::endl;
	}
	else {
		std::cout << structure.toString() << std::endl;
	}
	return true;
}
bool Parser::getCommand() {

	std::string id, key;

	if (file == "") {
		std::cout << "You are not working on any file." << std::endl;
		std::cout << "Try \'open\' or \'new\' to open/create file." << std::endl;
	}
	else {
		std::cout << "Get [prolog/attribute/text]> ";
		std::cin >> key;
		if (key == "prolog") {
			std::cout << "Prolog attribute [name]> ";
			std::cin >> key;
			Attribute* atr = structure.getPrologAttributeByName(key);
			if (atr) {
				std::cout << "Prolog attribute \'" << key << "\' has value: ";
				std::cout << "\'" << atr->getValue() << "\'." << std::endl;
			}
			else {
				std::cout << "No prolog attribute with name \'" << key << "\'." << std::endl;
				return true;
			}
		}
		else if (key == "attribute") {
			std::cout << "Element [id]> ";
			std::cin >> id;
			Element* elem = structure.getElementById(id);
			if (elem) {
				std::cout << "Element data [name]> ";
				std::cin >> key;
				std::cout << "Element data \'" << key << "\' has value: ";
				std::cout << "\'" << elem->getDataValueByName(key) << "\'." << std::endl;
			}
			else {
				std::cout << "No element with id \'" << id << "\'." << std::endl;
				return true;
			}
		}
		else if (key == "text") {
			std::cout << "Element [id]> ";
			std::cin >> id;
			Element* elem = structure.getElementById(id);
			if (elem) {
				std::cout << "Element with id \'" << id << "\' has text: ";
				std::cout << "\'" << elem->getText() << "\'." << std::endl;
			}
			else {
				std::cout << "No element with id \'" << id << "\'." << std::endl;
				return true;
			}
		}
		else {
			std::cout << "please choose one of the following: [prolog/attribute/text]." << std::endl;
		}
	}
	return true;
}
bool Parser::setCommand() {

	std::string content;
	std::string id, key, value;

	if (file == "") {
		std::cout << "You are not working on any file." << std::endl;
		std::cout << "Try \'open\' or \'new\' to open/create file." << std::endl;
	}
	else {
		std::cout << "Set [prolog/attribute/text]> ";
		std::cin >> key;
		if (key == "prolog") {
			std::cout << "Prolog attribute [name]> ";
			std::cin >> key;
			Attribute* atr = structure.getPrologAttributeByName(key);
			if (atr) {
				std::cout << "Set prolog attribute \'" << key << "\' to [value]> ";
				std::cin >> content;
				atr->setValue(content);
				std::cout << "Prolog attribute \'" << key << "\' has value: ";
				std::cout << "\'" << atr->getValue() << "\'." << std::endl;
			}
			else {
				std::cout << "No prolog attribute with name \'" << key << "\'." << std::endl;
				return true;
			}
		}
		else if (key == "attribute") {
			std::cout << "Element [id]> ";
			std::cin >> id;
			Element* elem = structure.getElementById(id);
			if (elem) {
				std::cout << "Element data [name]> ";
				std::cin >> key;
				std::cout << "Set element data to [value]> ";
				std::cin >> content;
				elem->setDataValueByName(key, content);
				std::cout << "Element data \'" << key << "\' has value: ";
				std::cout << "\'" << elem->getDataValueByName(key) << "\'." << std::endl;
			}
			else {
				std::cout << "No element with id \'" << id << "\'." << std::endl;
				return true;
			}
		}
		else if (key == "text") {
			std::cout << "Element [id]> ";
			std::cin >> id;
			Element* elem = structure.getElementById(id);
			if (elem) {
				std::cout << "Set element text to [value] (type \'&none;\' for empty string)> ";
				std::cin >> content;
				if (content == "&none;") content = "";
				elem->setText(content);
				std::cout << "Element with id \'" << id << "\' has text: ";
				std::cout << "\'" << elem->getText() << "\'." << std::endl;
			}
			else {
				std::cout << "No element with id \'" << id << "\'." << std::endl;
				return true;
			}
		}
		else {
			std::cout << "please choose one of the following: [prolog/attribute/text]." << std::endl;
		}
	}
	return true;
}
bool Parser::addCommand() {

	std::string content;
	std::string id, key, value;

	if (file == "") {
		std::cout << "You are not working on any file." << std::endl;
		std::cout << "Try \'open\' or \'new\' to open/create file." << std::endl;
	}
	else {
		std::cout << "Add [prolog/attribute/element]> ";
		std::cin >> key;
		if (key == "prolog") {
			std::cout << "Prolog attribute [name]> ";
			std::cin >> key;
			std::cout << "Prolog attribute [value]> ";
			std::cin >> content;
			structure.addPrologAttribute(key, content);
			std::cout << "Done." << std::endl;
		}
		else if (key == "attribute") {
			std::cout << "Element [id]> ";
			std::cin >> id;
			Element* elem = structure.getElementById(id);
			if (elem) {
				std::cout << "Aattribute [name]> ";
				std::cin >> key;
				std::cout << "Attribute [value]> ";
				std::cin >> content;
				elem->addAttribute(key, content);
				std::cout << "Done." << std::endl;
			}
			else {
				std::cout << "No element with id \'" << id << "\'." << std::endl;
				return true;
			}
		}
		else if (key == "element") {
			std::cout << "Element [id]> ";
			std::cin >> id;
			Element* elem = structure.getElementById(id);
			if (elem) {
				std::cout << "Element [key]> ";
				std::cin >> key;
				std::cout << "Element [id]> ";
				std::cin >> content;
				std::cout << "Element [text] (type \'&none;\' for empty string)> ";
				std::cin >> value;
				if (value == "&none;") value = "";
				structure.addElement(id, key, value, content);
				std::cout << "Done." << std::endl;
			}
			else {
				std::cout << "No element with id \'" << id << "\'." << std::endl;
				return true;
			}
		}
		else {
			std::cout << "please choose one of the following: [prolog/attribute/element]." << std::endl;
		}
	}
	return true;
}
bool Parser::removeCommand() {

	std::string id, key;

	if (file == "") {
		std::cout << "You are not working on any file." << std::endl;
		std::cout << "Try \'open\' or \'new\' to open/create file." << std::endl;
	}
	else {
		std::cout << "Remove [prolog/attribute/element]> ";
		std::cin >> key;
		if (key == "prolog") {
			std::cout << "Prolog attribute [name]> ";
			std::cin >> key;
			Attribute* atr = structure.getPrologAttributeByName(key);
			if (atr) {
				structure.removePrologAttribute(key);
				std::cout << "Done." << std::endl;
			}
			else {
				std::cout << "No prolog attribute with name \'" << key << "\'." << std::endl;
				return true;
			}
		}
		else if (key == "attribute") {
			std::cout << "Element [id]> ";
			std::cin >> id;
			Element* elem = structure.getElementById(id);
			if (elem) {
				std::cout << "Attribute [name]> ";
				std::cin >> key;
				structure.removeAttribute(id, key);
				std::cout << "Done." << std::endl;
			}
			else {
				std::cout << "No element with id \'" << id << "\'." << std::endl;
				return true;
			}
		}
		else if (key == "element") {
			std::cout << "Element [id]> ";
			std::cin >> id;
			Element* elem = structure.getElementById(id);
			if (elem) {
				structure.removeElement(id);
				std::cout << "Done." << std::endl;
			}
			else {
				std::cout << "No element with id \'" << id << "\'." << std::endl;
				return true;
			}
		}
		else {
			std::cout << "please choose one of the following: [prolog/attribute/element]." << std::endl;
		}
	}
	return true;
}
bool Parser::XPathCommand() {

	std::string content;
	std::string id;

	if (file == "") {
		std::cout << "You are not working on any file." << std::endl;
		std::cout << "Try \'open\' or \'new\' to open/create file." << std::endl;
	}
	else {
		std::cout << "XPath from element [id] (type \'&root;\' for root element)> ";
		std::cin >> id;
		if (id == "&root;") id = structure.getRootId();
		std::cout << "[XPath]> ";
		std::cin >> content;
		std::cout << "XPath result:" << std::endl;
		std::cout << Path::Pathh(content, id, structure) << std::endl;
	}
	return true;
}
bool Parser::helpCommand() {
	std::cout << "Available commands:" << std::endl;
	std::cout << "\tforceexit    - description ;)" << std::endl;
	std::cout << "\texit         - description ;)" << std::endl;
	std::cout << "\topen         - description ;)" << std::endl;
	std::cout << "\tnew          - description ;)" << std::endl;
	std::cout << "\tclose        - description ;)" << std::endl;
	std::cout << "\tsave         - description ;)" << std::endl;
	std::cout << "\tsaveAs       - description ;)" << std::endl;
	std::cout << "\tprint        - description ;)" << std::endl;
	std::cout << "\tget          - description ;)" << std::endl;
	std::cout << "\tset          - description ;)" << std::endl;
	std::cout << "\tadd          - description ;)" << std::endl;
	std::cout << "\tremove       - description ;)" << std::endl;
	std::cout << "\tXPath        - description ;)" << std::endl;
	return true;
}
bool Parser::notFoundCommand(std::string command) {
	std::cout << "Command not found: \'" << command << "\'. ";
	std::cout << "Try \'help\' for more information." << std::endl;
	return true;
}