#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <string>
#include "Element.h"

class Structure {

public:
	Structure(std::string key = "root", std::string id = "0");
	void setRootValues(std::string key, std::string id);
	std::string addElement(std::string id, std::string newKey, std::string newText = "", std::string newId = "");
	bool removeElement(std::string id);
	void setText(std::string id, std::string text);
	void appendText(std::string id, std::string text);
	std::string getText(std::string id);
	Element* getElementById(std::string id);
	void addAttribute(std::string id, std::string name, std::string value);
	void setAttributeValue(std::string id, std::string name, std::string value);
	bool removeAttribute(std::string id, std::string attributeName);
	void addPrologAttribute(std::string name, std::string value);
	int sizePrologAttribute() const;
	Attribute* getPrologAttribute(int i);
	void removePrologAttribute(std::string name);
	Attribute* getPrologAttributeByName(std::string name);
	std::string getRootId() const;
	const Element getRootElement() const;
	void fillVectorWithElements(std::string id, std::vector<Element>& elements);
	std::string toString() const;
private:
	void fillVectorWithElementsRecursive(Element* current, std::vector<Element>& elements);
	Element* findElementRecursive(Element* current, std::string id);
	Element* findElement(std::string id);
	Element* findElementParentRecursive(Element* current,std::string id);
	Element* findElementParent(std::string id);
	std::string getFreeId(std::string id);
	bool isIdFree(std::string id);

	std::vector<Attribute> prolog;
	std::vector<std::string> usedId;
	Element root;

};

#endif