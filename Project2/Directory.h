#pragma once
#include "DirectoryNode.h"
#include "Queue.h"
#include "DirectoryNodeStack.h"
#include "stringTree.h"
#include <string>
#include <iostream>

class Directory
{
public:
	Directory();
	~Directory();
	DirectoryNodeStack<DirectoryNode> stack;

	void add(std::string name);

	//movement
	void gotoSub();
	bool gotoNext();
//	void gotoFirst() { curr = curr->first; }
	void gotoRoot();
	bool gotoDir(std::string dir);
	bool goup();

	//listing
	void listDirectories();

	//returns
	std::string getCurr() { return curr->name; };

	//extra
	void clone(std::string dir);

	//delete
	void deleteDir(std::string);

	//path
	std::string getPath();
private:
	DirectoryNode* curr, * root;

	bool getToDirectory(std::string dir);	//takes an absolute path, changes dir input to only destination
	bool gotoDirectory(std::string path);

	void queify(DirectoryNode* pos, Queue<DirectoryNode>*& queue);
	void replaceQ(Queue<DirectoryNode>*& queue1, Queue<DirectoryNode>*& queue2);
	void clearq(Queue<DirectoryNode>*& queue);

	bool delNode(DirectoryNode* returnPoint, std::string dir);

	void gotoPrior();
};



//Directory structure diagram
// NOTE: Sub-directories are doubly linked, ensure prior and next are accounted for while traversing 
//   curr|
//       \/
//----------
//|   root | ------> nullptr
//|        |
//----------
//	 |
//	 | sub
//   \/					last \/
//----------	next	---------
//| L      | ------ >	|W		| -----> nullptr
//|        | <------	|		|
//----------	prior	---------
//		|					|
//		|sub				|sub
//     \/					\/
//	nullptr				nullptr
//
//











