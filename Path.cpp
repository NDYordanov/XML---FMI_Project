#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Attribute.h"
#include "Element.h"
#include "Structure.h"
#include "Validator.h"
#include "Path.h"

//using namespace std;


std::string Path::Pathh(std::string command, std::string id, Structure& xmls) {
	std::vector<Element> elements;
	xmls.fillVectorWithElements(id, elements);
	Path x;
	command += '/';

	bool at;
	std::string elementName = "", attributeName = "", attributeValue = "";

	for (int i = 0; i < command.size(); i++) {
		at = false;
		x.skipToXPathSing(i, command, elementName);
		if (command[i] == '/') {
			if (command[i + 1] == '/' or command[i + 1] == '(' or command[i + 1] == '[')
				return "ERROR: ILLIGAL SIGN AFTER '/'";
			// cout << "get elements with key -" << elementName << "-" << endl;
			x.removeElementsByTag(elements, elementName);
		}
		else if (command[i] == '[') {
			i++;
			int index;
			x.skipToChar(i, ']', command, attributeValue);
			if (!x.stringToInt(attributeValue, index)) return "ERROR: BAD INDEX VALUE";
			i++;
			if (command[i] != '/') return "ERROR: EXPECTED '/' AFTER ']'";
			// cout << "get element -" << elementName << "- ";
			// cout << "with index -" << index << "-" << endl; 
			x.removeElementsByTag(elements, elementName);
			x.removeElementsByIndex(elements, index);
		}
		else if (command[i] == '(') {
			i++;
			if (command[i] == '@') {
				at = true;
				i++;
				x.skipToChar(i, ')', command, attributeName);
				i++;
				if (command[i] != '/') return "ERROR: EXPECTED '/' AFTER ']'";
				// cout << "get elements with key -" << elementName << "- ";
				// cout << "that have attribute -" << attributeName << "-" << endl;
				x.removeElementsByTag(elements, elementName);
				x.removeElementsByAttribute(elements, attributeName);
			}
			else {
				x.skipToChar(i, '=', command, attributeName);
				i++;
				if (command[i] != '"') return "ERROR: ATTRIBUTE VALUE MUST BE QUOTED";
				else {
					i++;
					x.skipToChar(i, '"', command, attributeValue);
				}
				i++;
				if (command[i] != ')') return "ERROR: EXPECTED ')' AFTER '\"'";
				i++;
				if (command[i] != '/') return "ERROR: EXPECTED '/' AFTER ']'";
				// cout << "get elements with key -" << elementName << "- ";
				// cout << "that has -" << attributeName << "- ";
				// cout << "equals to -" << attributeValue << "-" << endl;
				x.removeElementsByTag(elements, elementName);
				x.removeElementsByData(elements, attributeName, attributeValue);
			}
		}
	}
	std::string result = "";
	if (at) {
		for (int i = 0; i < elements.size(); i++) {
			std::string temp = elements[i].getDataValueByName(attributeName);
			if (temp != "") result += temp + "\n";
		}
	}
	else {
		for (int i = 0; i < elements.size(); i++) {
			std::string temp = elements[i].getText();
			if (temp != "") result += temp + "\n";
		}
	}
	return result;
}


void Path::removeElementsByTag(std::vector<Element>& elements, std::string tagName) {
	std::vector<Element> result;
	for (int i = 0; i < elements.size(); i++) {
		if (elements[i].hasChildElement(tagName)) {
			for (int x = 0; x < elements[i].sizeChildElement(); x++) {
				Element* temp = elements[i].getChildElement(x);
				if (temp->getKey() == tagName) {
					result.push_back(*temp);
				}
			}
		}
	}
	elements.clear();
	for (int i = 0; i < result.size(); i++) {
		elements.push_back(result[i]);
	}
}
void Path::removeElementsByIndex(std::vector<Element>& elements, int index) {
	Element x = elements[index];
	elements.clear();
	elements.push_back(x);
}
void Path::removeElementsByAttribute(std::vector<Element>& elements, std::string dataName) {
	std::vector<Element> result;
	for (int i = 0; i < elements.size(); i++) {
		if (elements[i].hasDataName(dataName) or elements[i].hasChildElement(dataName)) {
			Element temp = elements[i];
			result.push_back(temp);
		}
	}
	elements.clear();
	for (int i = 0; i < result.size(); i++) {
		elements.push_back(result[i]);
	}
}
void Path::removeElementsByData(std::vector<Element>& elements, std::string dataName, std::string dataValue) {
	std::vector<Element> result;
	for (int i = 0; i < elements.size(); i++) {
		if (elements[i].hasData(dataName, dataValue)) {
			Element temp = elements[i];
			result.push_back(temp);
		}
	}
	elements.clear();
	for (int i = 0; i < result.size(); i++) {
		elements.push_back(result[i]);
	}
}

bool Path::skipToXPathSing(int& i, std::string content, std::string& data) {
	data = "";
	while (i < content.size()) {
		data += content[i++];
		if (content[i] == '/' or content[i] == '(' or content[i] == '[') return true;
	}
	return false;
}


bool Path::skipToChar(int& i, char x, std::string content, std::string& data) {
	data = "";
	while (i < content.size()) {
		data += content[i++];
		if (content[i] == x) return true;
	}
	return false;
}


bool Path::stringToInt(std::string data, int& ind) {
	ind = 0;
	for (int i = 0; i < data.size(); i++) {
		if (data[i] < '0' || data[i] > '9') return false;
		ind *= 10;
		ind += data[i] - '0';
	}
	return true;
}