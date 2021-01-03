#pragma once



#include <string>
#include <iostream>




class BSNode
{
public:
	//inits a junction
	BSNode(std::string data);

	//deep copy of another tree
	BSNode(const BSNode& other);
	~BSNode();

	BSNode* getLeft() const;
	BSNode* getRight() const;
	bool isLeaf() const;
	void insert(std::string value);
	bool search(std::string value) const;
	std::string getData() const;
	BSNode& operator=(const BSNode& other);

	void printNodesConsole() const;

	//assumes input node is a direct ancestor of curr node
	//returns -1 if not
	int getCurrNodeDistFromInputNode(const BSNode* ancestor) const;
	int getDepth(const BSNode& root) const;
	int getHeight() const;
private:
	std::string _data;
	BSNode* _left;
	BSNode* _right;
	int _count;
};

