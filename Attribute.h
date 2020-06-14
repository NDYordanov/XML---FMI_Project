#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <string>

class Attribute {
public:
	Attribute(std::string name, std::string value);

	void set(std::string name, std::string value);
	void setName(std::string name);
	void setValue(std::string value);

	std::string getName() const;
	std::string getValue() const;
	std::string toString() const;
private:
	void doSetName(std::string name);
	void doSetValue(std::string value);
	std::string name;
	std::string value;
};

#endif