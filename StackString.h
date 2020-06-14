#ifndef STACKSTRING_H
#define STACKSTRING_H
#include <string>

struct StackStringNode {
	std::string data;
	StackStringNode* last;
};

class StackString {
public:
	StackString();
	StackString(const StackString& other);
	StackString& operator=(const StackString& other);
	~StackString();

	bool empty();
	void push(std::string data);
	bool pop();
	std::string top();

private:
	void doCopy(const StackString& other);
	void doCopyRecursive(StackStringNode* node);
	void doDelete();
	void doAddNode(std::string data);
	void doDeleteTopNode();

	StackStringNode* current;
};

#endif