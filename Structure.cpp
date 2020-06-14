#include "Structure.h"
//#include "Element.h"
#include "Attribute.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//using namespace std;

Structure::Structure(std::string key, std::string id) {
	this->root = Element(key, "", id);
	this->usedId.push_back("");
	this->usedId.push_back("0");
}

void Structure::setRootValues(std::string key, std::string id) {
	this->root.setKey(key);
	this->root.setId(this->getFreeId(id));
	this->usedId.push_back(this->root.getId());
}

std::string Structure::addElement(std::string id, std::string newKey, std::string newText, std::string newId) {
	Element* temp = this->findElement(id);
	if (temp) {
		newId = this->getFreeId(newId);
		this->usedId.push_back(newId);
		temp->addChildElement(newKey, newText, newId);
		return newId;
	}
	return "";
}

bool Structure::removeElement(std::string id) {
	Element* temp = findElementParent(id);
	if (temp) {
		for (int i = 0; i < temp->sizeChildElement(); i++) {
			if (temp->getChildElement(i)->getId() == id) {
				temp->removeChildElement(i);
				return true;
			}
		}
	}
	return false;
}

void Structure::setText(std::string id, std::string text) {
	Element* temp = findElement(id);
	if (temp) {
		temp->setText(text);
	}
}

void Structure::appendText(std::string id, std::string text) {
	Element* temp = findElement(id);
	if (temp) {
		if (temp->getText() != "") {
			temp->setText(temp->getText() + " " + text);
		}
		else {
			temp->setText(temp->getText() + text);
		}
	}
}

std::string Structure::getText(std::string id) {
	Element* temp = findElement(id);
	if (temp) {
		return temp->getText();
	}
	else {
		return "";
	}
}

Element* Structure::getElementById(std::string id) {
	Element* temp = findElement(id);
	return temp;
}

void Structure::addAttribute(std::string id, std::string name, std::string value) {
	Element* temp = this->findElement(id);
	if (temp) {
		temp->addAttribute(name, value);
	}
}

void Structure::setAttributeValue(std::string id, std::string name, std::string value) {
	Element* temp = this->findElement(id);
	if (temp) {
		for (int i = 0; i < temp->sizeAttribute(); i++) {
			if (temp->getAttribute(i)->getName() == name) {
				temp->getAttribute(i)->setValue(value);
			}
		}
	}
}

bool Structure::removeAttribute(std::string id, std::string attributeName) {
	Element* temp = this->findElement(id);
	if (temp) {
		for (int i = 0; i < temp->sizeAttribute(); i++) {
			if (temp->getAttribute(i)->getName() == attributeName) {
				temp->removeAttribute(i);
				return true;
			}
		}
	}
	return false;
}

void Structure::addPrologAttribute(std::string name, std::string value) {
	this->prolog.push_back(Attribute(name, value));
}

int Structure::sizePrologAttribute() const {
	return this->prolog.size();
}

Attribute* Structure::getPrologAttribute(int i) {
	return &(this->prolog[i]);
}

void Structure::removePrologAttribute(std::string name) {
	for (int i = 0; i < this->prolog.size(); i++) {
		if (this->prolog[i].getName() == name) {
			this->prolog.erase(this->prolog.begin() + i);
			return;
		}
	}
}

Attribute* Structure::getPrologAttributeByName(std::string name) {
	for (int i = 0; i < this->prolog.size(); i++) {
		if (this->prolog[i].getName() == name) {
			return &(this->prolog[i]);
		}
	}
	return nullptr;
}

std::string Structure::getRootId() const {
	return this->root.getId();
}

const Element Structure::getRootElement() const {
	return this->root;
}

std::string Structure::toString() const {
	std::string ret = "";
	if (this->prolog.size()) {
		ret += "<?xml";
		for (int i = 0; i < this->prolog.size(); i++) {
			ret += this->prolog[i].toString();
		}
		ret += "?>\n";
	}
	ret += this->root.toString();
	return ret;
}
void Structure::fillVectorWithElements(std::string id, std::vector<Element>& elements) {
	Element* temp = findElement(id);
	if (temp) {
		Element current = *temp;
		elements.push_back(current);
		this->fillVectorWithElementsRecursive(&current, elements);
	}
}

void Structure::fillVectorWithElementsRecursive(Element* current, std::vector<Element>& elements) {
	Element next;
	for (int i = 0; i < current->sizeChildElement(); i++) {
		next = *(current->getChildElement(i));
		elements.push_back(next);
		this->fillVectorWithElementsRecursive(&next, elements);
	}
}

Element* Structure::findElementRecursive(Element* current, std::string id) {

	if (current->getId() == id) return current;

	for (int i = 0; i < current->sizeChildElement(); i++) {

		Element* temp = findElementRecursive(current->getChildElement(i), id);
		if (temp) {
			return temp;
		}
	}
	return nullptr;
}

Element* Structure::findElement(std::string id) {
	return findElementRecursive(&this->root, id);
}

Element* Structure::findElementParentRecursive(Element* current, std::string id) {

	for (int i = 0; i < current->sizeChildElement(); i++) {
		if (current->getChildElement(i)->getId() == id) {
			return current;
		}
		Element* temp = findElementRecursive(current->getChildElement(i), id);
		if (temp) {
			return temp;
		}
	}
	return nullptr;
}

Element* Structure::findElementParent(std::string id) {
	return findElementParentRecursive(&this->root, id);
}

std::string Structure::getFreeId(std::string id) {
	if (isIdFree(id)) return id;
	int i = 1;
	while (1) {
		if (isIdFree(id + "_" + std::to_string(i)))
			return id + "_" + std::to_string(i);
		i++;
	}
}

bool Structure::isIdFree(std::string id) {
	for (int i = 0; i < usedId.size(); i++) {
		if (usedId[i] == id)
			return false;
	}
	return true;
}