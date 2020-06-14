#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include <vector>
#include "Attribute.h"
//#include "Element.h"

class Element {
public:
	Element(std::string key = "", std::string text = "", std::string id = "");
	void set(std::string key, std::string text);
	void set(std::string key, std::string text, std::string id);
	void setKey(std::string key);
	void setText(std::string text);
	void setId(std::string id);
	std::string getKey() const;
	std::string getText() const;
	std::string getId() const;
	void addChildElement(std::string key, std::string text = "", std::string id = "");
	int sizeChildElement() const;
	Element* getChildElement(int i);
	void removeChildElement(int i);
	void addAttribute(std::string name, std::string value = "");
	int sizeAttribute() const;
	Attribute* getAttribute(int i);
	void removeAttribute(int i);
	bool hasChildElement(std::string key);
	bool hasDataName(std::string name);
	std::string getDataValueByName(std::string name);
	void setDataValueByName(std::string name, std::string value);
	bool hasData(std::string dataName, std::string dataValue);
	std::string toString(int tabs = 0) const;

private:
	void doSetKey(std::string key);
	void doSetText(std::string text);
	void doSetId(std::string id);
	std::string tabsString(int tabs) const;
	std::string id;
	std::string key;
	std::string text;
	std::vector< Attribute > attributes;
	std::vector< Element > childElements;
};

#endif