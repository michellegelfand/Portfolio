#include "BSNode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "BSNode.h" //string BSTree
#include "printTreeToFile.h" //to use with string BSNode class only, not with templates
#include "TBSNode.h" //template BSTree


#pragma comment(lib, "printTreeToFile.lib")
using std::cout;
using std::endl;


int main()
{
	BSNode* bs = new BSNode("6");
	bs->insert("911");
	bs->insert("8");
	bs->insert("3");
	bs->insert("4");
	bs->insert("9");
	bs->insert("6");
	bs->insert("3");
	//bs->printNodesConsole();
	
	
	//std::cout << "leaks: " << _CrtDumpMemoryLeaks();
	
	std::string textTree = "BSTData.txt";
	printTreeToFile(bs, textTree);

	system("BinaryTree.exe");
	system("pause");
	remove(textTree.c_str());
	//cout << bs->getHeight();
	bs->printNodesConsole();
	cout << "\n\n\n\n\n";
	BSNode* below = (bs->getLeft())->getRight();
	//cout << endl << below->getDepth(*bs);
	delete bs;

	TBSNode<int> bst(12);
	bst.insert(11);
	bst.insert(100);
	bst.insert(95);
	bst.insert(30);
	bst.insert(-1);
	bst.insert(9);

	bst.printNodesConsole();

	return 0;
}
/*
int main1()
{
	BSNode* bs = new BSNode("6");
	bs->insert("2");
	bs->insert("8");
	bs->insert("3");
	bs->insert("5");
	bs->insert("9");
	bs->insert("6");


	//cout << "Tree height: " << bs->getHeight() << endl;
	//cout << "depth of node with 5 depth: " << bs->getLeft()->getRight()->getRight()->getDepth(*bs) << endl;
	//cout << "depth of node with 3 depth: " << bs->getLeft()->getRight()->getDepth(*bs) << endl;


	std::string textTree = "BSTData.txt";
	printTreeToFile((const BSNode*)bs, textTree);

	system("BinaryTree.exe");
	system("pause");
	//remove(textTree.c_str());
	//delete bs;

	return 0;
}

*/