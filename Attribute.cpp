#include "Attribute.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//using namespace std;

Attribute::Attribute(std::string name, std::string value) {
	this->doSetName(name);
	this->doSetValue(value);
	//this->name = name;
	//this->value = value;
}

void Attribute::set(std::string name, std::string value) {
	this->doSetName(name);
	this->doSetValue(value);
	//this->name = name;
	//this->value = value;
}

void Attribute::setName(std::string name) {
	this->doSetName(name);
	//this->name = name;
}
void Attribute::setValue(std::string value) {
	this->doSetValue(value);
	//this->value = value;
}

std::string Attribute::getName() const {
	return this->name;
}
std::string Attribute::getValue() const {
	return this->value;
}

std::string Attribute::toString() const {
	return " " + name + "=\"" + value + "\"";
}

void Attribute::doSetName(std::string name) {
	this->name = name;
}

void Attribute::doSetValue(std::string value) {
	this->value = value;
}