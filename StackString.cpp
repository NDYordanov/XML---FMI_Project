#include "StackString.h"
#include <iostream>
#include <string>
//using namespace std;

StackString::StackString() {
	this->current = nullptr;
}
StackString::StackString(const StackString& other) {
	this->doCopy(other);
}
StackString& StackString::operator=(const StackString& other) {
	if (this != &other) {
		this->doDelete();
		this->doCopy(other);
	}
	return *this;
}
StackString::~StackString() {
	this->doDelete();
}

bool StackString::empty() {
	return !((bool)this->current);
}
void StackString::push(std::string data) {
	this->doAddNode(data);
}
bool StackString::pop() {
	if (this->current) {
		this->doDeleteTopNode();
		return true;
	}
	return false;
}
std::string StackString::top() {
	std::string data;
	if (this->current) {
		data = this->current->data;
	}
	return data;
}


void StackString::doCopy(const StackString& other) {
	doCopyRecursive(other.current);
}
void StackString::doCopyRecursive(StackStringNode* node) {
	if (node) {
		doCopyRecursive(node->last);
		this->doAddNode(node->data);
	}
}
void StackString::doDelete() {
	while (this->current) {
		this->doDeleteTopNode();
	}
}
void StackString::doAddNode(std::string data) {
	StackStringNode* temp = new StackStringNode;
	temp->data = data;
	temp->last = current;
	current = temp;
}
void StackString::doDeleteTopNode() {
	StackStringNode* temp = this->current->last;
	delete this->current;
	this->current = temp;
}