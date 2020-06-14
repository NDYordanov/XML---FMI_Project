#include "Element.h"
//#include "Attribute.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//using namespace std;


Element::Element(std::string key, std::string text, std::string id) {
	doSetKey(key);
	doSetText(text);
	doSetId(id);
}

void Element::set(std::string key, std::string text) {
	doSetKey(key);
	doSetText(text);
}

void Element::set(std::string key, std::string text, std::string id) {
	doSetKey(key);
	doSetText(text);
	doSetId(id);
}

void Element::setKey(std::string key) {
	doSetKey(key);
}

void Element::setText(std::string text) {
	doSetText(text);
}

void Element::setId(std::string id) {
	doSetId(id);
}

std::string Element::getKey() const {
	return this->key;
}

std::string Element::getText() const {
	return this->text;
}

std::string Element::getId() const {
	return this->id;
}

void Element::addChildElement(std::string key, std::string text, std::string id) {
	this->childElements.push_back(Element(key, text, id));
}

int Element::sizeChildElement() const {
	return this->childElements.size();
}

Element* Element::getChildElement(int i) {
	return &(this->childElements[i]);
}

void Element::removeChildElement(int i) {
	this->childElements.erase(this->childElements.begin() + i);
}

void Element::addAttribute(std::string name, std::string value) {
	if (name == "id") return;
	this->attributes.push_back(Attribute(name, value));
}

int Element::sizeAttribute() const {
	return this->attributes.size();
}

Attribute* Element::getAttribute(int i) {
	return &(this->attributes[i]);
}

void Element::removeAttribute(int i) {
	this->attributes.erase(this->attributes.begin() + i);
}

bool Element::hasChildElement(std::string key) {
	for (int i = 0; i < this->childElements.size(); i++) {
		if (this->childElements[i].getKey() == key) {
			return true;
		}
	}
	return false;
}


bool Element::hasDataName(std::string name) {
	if (name == "id" and this->id != "") return true;
	for (int i = 0; i < this->attributes.size(); i++) {
		if (this->attributes[i].getName() == name) {
			return true;
		}
	}
	for (int i = 0; i < this->childElements.size(); i++) {
		if (this->childElements[i].getKey() == name) {
			return true;
		}
	}
	return false;
}

std::string Element::getDataValueByName(std::string name) {
	if (name == "id") return this->id;
	for (int i = 0; i < this->attributes.size(); i++) {
		if (this->attributes[i].getName() == name) {
			return this->attributes[i].getValue();
		}
	}
	for (int i = 0; i < this->childElements.size(); i++) {
		if (this->childElements[i].getKey() == name) {
			return this->childElements[i].getText();
		}
	}
	return "";
}
void Element::setDataValueByName(std::string name, std::string value) {
	for (int i = 0; i < this->attributes.size(); i++) {
		if (this->attributes[i].getName() == name) {
			return this->attributes[i].setValue(value);
		}
	}
	for (int i = 0; i < this->childElements.size(); i++) {
		if (this->childElements[i].getKey() == name) {
			return this->childElements[i].setText(value);
		}
	}
}

bool Element::hasData(std::string dataName, std::string dataValue) {
	if (dataName == "id" and dataValue == this->id) return true;
	for (int i = 0; i < this->childElements.size(); i++) {
		if (this->childElements[i].getKey() == dataName) {
			if (this->childElements[i].getText() == dataValue) {
				return true;
			}
		}
	}
	for (int i = 0; i < this->attributes.size(); i++) {
		if (this->attributes[i].getName() == dataName) {
			if (this->attributes[i].getValue() == dataValue) {
				return true;
			}
		}
	}
	return false;
}

std::string Element::toString(int tabs) const {
	std::string ret = "";

	/// (\t<KEY id="ID")
	ret += this->tabsString(tabs);
	ret += "<";
	ret += this->key;
	ret += " id=\"";
	ret += this->id;
	ret += "\"";

	/// n:( NAME="VALUE")
	for (int i = 0; i < this->attributes.size(); i++) {
		ret += this->attributes[i].toString();
	}

	if (this->childElements.empty()) {
		/// (>TEXT</KEY>)
		ret += ">";
		ret += this->text;
		ret += "</";
		ret += this->key;
		ret += ">";
		return ret;
	}

	/// (>TEXT\n)
	ret += ">";
	ret += this->text;

	/// n:(CHILDELEMENT\n)
	for (int i = 0; i < this->childElements.size(); i++) {
		ret += "\n";
		ret += this->childElements[i].toString(tabs + 1);
	}
	ret += "\n";

	/// (\t</KEY>)
	ret += this->tabsString(tabs);
	ret += "</";
	ret += this->key;
	ret += ">";

	return ret;
}

void Element::doSetKey(std::string key) {
	if (key == "") key = "unknown";
	this->key = key;
}

void Element::doSetText(std::string text) {
	this->text = text;
}

void Element::doSetId(std::string id) {
	this->id = id;
}

std::string Element::tabsString(int tabs) const {
	std::string ret = "";
	for (int i = 0; i < tabs; i++) {
		ret += "\t";
	}
	return ret;
}