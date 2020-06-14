#ifndef PATH_H
#define PATH_H
#include <string>

class Path {
public:
	static std::string Pathh(std::string command, std::string id, Structure& xml);
private:
	void removeElementsByTag(std::vector<Element>& elements, std::string tagName);
	void removeElementsByIndex(std::vector<Element>& elements, int index);
	void removeElementsByAttribute(std::vector<Element>& elements, std::string dataName);
	void removeElementsByData(std::vector<Element>& elements, std::string dataName, std::string dataValue);

	bool skipToChar(int& i, char x, std::string content, std::string& data);
	bool skipToXPathSing(int& i, std::string content, std::string& data);
	bool stringToInt(std::string data, int& index);
};

#endif