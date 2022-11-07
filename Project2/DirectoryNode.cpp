#include "DirectoryNode.h"

DirectoryNode::DirectoryNode()
{
	//for subDirectories 

	//first = this;
	last = this;
	sub = nullptr;
	prior = nullptr;

	//for next
	next = nullptr;
}
 