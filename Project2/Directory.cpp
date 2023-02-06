#include "Directory.h"

Directory::Directory()
{
	DirectoryNode* newDir = new DirectoryNode;
	newDir->name = "ROOT";
	root = newDir;
	curr = newDir;
}

Directory::~Directory()
{

}

void Directory::add(std::string name)
{
	DirectoryNode* newDir = new DirectoryNode;
	newDir->name = name;
	if (curr->sub == nullptr)
	{
		curr->sub = newDir;
		return;
	}
	if (curr->sub->last != nullptr)
	{
		newDir->prior = curr->sub->last;
	}
	curr->sub->last->next = newDir; //WARNING is covered by checks above
	curr->sub->last = newDir;
}

void Directory::gotoSub() 
{
	if (curr->sub != nullptr)
	{
		stack.push(curr);
		curr = curr->sub;
	}
}

bool Directory::gotoNext()
{
	if (curr->next != nullptr)
	{
		curr = curr->next;
		return true;
	}
	return false;
}

void Directory::gotoRoot()
{
	curr = root;
	while (!stack.empty()) // clears the node stack
	{
		DirectoryNode* e;
		stack.pop(e);
	}
}

bool Directory::gotoDir(std::string dir)
{
	if (dir.find("/") == std::string::npos) //relative path
	{
		return gotoDirectory(dir);
	}
	//absolute path
	if (getToDirectory(dir))
	{
		return true;
	}
	gotoRoot(); //gotoRoot as getToDirectory could strand you in the furthest directory it got to before failing
	std::cout << "-----Error getting to [" << dir << "]-----\n";
	return false;
}

bool Directory::goup()
{
	DirectoryNode* val;
	if (stack.pop(val))
	{
		curr = val;
		return true;
	}
	return false;
}

void Directory::listDirectories()
{
	StringTree* tree = new StringTree;

	if (curr->sub != nullptr)
	{
		gotoSub();
		//gotoFirst();
		while (true)
		{
			tree->add(curr->name);
			if (!gotoNext())
			{
				break;
			}
		}
		std::cout << std::endl;
		goup();
	}
	else
	{
		std::cout << "-Empty Dir-\n";
		return;
	}
	tree->gotoFirst();
	std::string e = "";
	while (!tree->atEnd())
	{
		tree->getCurr(e);
		std::cout << e << "  ";
		tree->gotoNext();
	}
	std::cout << std::endl;
}

/// <summary>
///	This function runs through the directories being cloned at the same time as it creates them in the dir location.
///			|					|					|					|
///			|					|					|					|
///			|					|					|					|
///			| cloned directory	|					| dir location		|
///			|					|					|					|
///			|					|					|					|
///		It helps to think of the cloned directory and the dir location as being ran through in parallel. 
///		As we get directories A, B, C from cloned directory they are then added by queify to dir location
///		Then we go into A's subdirectories if any and do the same thing. Once A's subdirectories and next 
///		directories are exhausted the function calls goup then attempts to find the next subdirectory
///		This repeats until the directoryStack is empty.
/// </summary>
/// <param name="dir">The location to copy the current directory and subdirectories to</param>
void Directory::clone(std::string dir)
{
	DirectoryNodeStack<Queue<DirectoryNode>>* queueStack = new DirectoryNodeStack<Queue<DirectoryNode>>; 
	DirectoryNodeStack<DirectoryNode>* directoryStack = new DirectoryNodeStack <DirectoryNode>;

	//pos used to navigate the directory being cloned, hold holds the intial pos position. Do not change hold
	DirectoryNode* pos = (curr->sub != nullptr) ? curr->sub : curr;		//pos is used to traverse the cloned side at the same time as creating its elements at the dir location
	DirectoryNode* hold = pos;

	//go to the clone directory
	getToDirectory(dir);
	DirectoryNode* cloneDir = curr;

	//initial queue, "current" level of the directory structure
	Queue<DirectoryNode>* queue = new Queue<DirectoryNode>;
	queify(pos, queue);	//add queues elements to the clone directory
	
	std::string path;
	bool run = true;
	while (run)
	{
		while (true)
		{
			queue->dequeue(pos);
			while (pos->sub != nullptr)		//continue until at the very bottom left
			{
				queueStack->push(queue);

				//gets the path of the next location and attempts to go to it in the clone directory
				path = getPath() + "/" + pos->name;
				while (!getToDirectory(path)) {	
					goup();
					path = getPath() + "/" + pos->name;
				};
				pos = pos->sub;
				queify(pos, queue);	//add queues elements to the clone directory
				break;
			}
			if (queue->empty()) { break; }
		}	 
		if (queueStack->empty()) { run = false; break; };		//if queueStack is empty then the clone function has finished
		if (!queueStack->empty())	//if stack is not empty then pop its queue and use that for cloning
		{
			Queue<DirectoryNode>* q = new Queue<DirectoryNode>;
			queueStack->pop(q);
			replaceQ(q, queue);
		}
	}
	gotoRoot();
}

void Directory::deleteDir(std::string dir)
{
	DirectoryNode* returnPoint = curr;
	gotoDir(dir);
	while (curr != returnPoint)
	{
		if (delNode(returnPoint, dir)) 
		{
			//if (curr == returnPoint) { goup(); }
			break;
		};
	}
	
}

/// <summary>
/// Only deletes a singular node, will go as far to the "right" and "down" as possible then deletes that
/// Moves based off of current
/// </summary>
/// <param name="returnPoint">return point is the directory the delete was called from</param>
bool Directory::delNode(DirectoryNode* returnPoint, std::string dir)
{
	DirectoryNode *prior, *tempNode, *next;
	DirectoryNode* sub = nullptr;
	bool found = false;

	if (curr->sub == nullptr && curr->name == dir) { found = true; }

	//moving to last element
	if ((curr->next != nullptr) && curr->name != dir)
	{
		gotoNext();
		return false;
	}
	if (curr->sub != nullptr)
	{
		gotoSub();
		return false;
	}

	//deletes the node 
	tempNode = curr;

	if ((curr->prior != nullptr)) //if not first element
	{
		prior = curr->prior;
		next = curr->next;
		delete tempNode;
		curr = prior;
		curr->next = next;
		if (curr->next != nullptr) {
			curr->next->prior = curr;
		}
		goup();
		return found;
	}
	if (curr->next != nullptr) //if is first element with next element
	{ 
		sub = curr->next;
		sub->prior = nullptr;
		curr->next = sub->next;
		if (sub->next != nullptr) {
			sub->next->prior = sub;
		}
	}
	delete tempNode;  //code below runs for both instances of first w next elem and first wo next elem
	curr = nullptr;
	goup();
	curr->sub = sub;
	return found;
}

void Directory::gotoPrior()
{
	if (curr->prior != nullptr)
	{
		curr = curr->prior;
	}
}

//handles absolute path
bool Directory::getToDirectory(std::string dir) //helper function
{
	std::string currDirSearch;
	std::size_t posOfDash;

	while (dir.find("/") != std::string::npos) //goes to level above directory
	{
		posOfDash = dir.find("/");
		currDirSearch = dir.substr(0, posOfDash);
		dir = dir.substr(posOfDash + 1);
		if (currDirSearch == "ROOT")
		{
			gotoRoot();
		}
		if (!gotoDirectory(currDirSearch) && !(currDirSearch.length() == 0) && currDirSearch != "ROOT")
		{
			std::cout << "-----Error Getting to Directory-----\n";
			return false;
		}
	}
	return gotoDirectory(dir); //goes into directory
}

//handles relative path
bool Directory::gotoDirectory(std::string path) //helper function for gotoDir
{
	if (curr->sub != nullptr)
	{
		gotoSub();
	//	gotoFirst();
		while (true)
		{
			if (getCurr() == path)
			{
				return true;
			}
			if (!gotoNext())
			{
				goup();
				return false;
			}
		}
	}
}

/// <summary>
/// Adds the elements from the queue to the current directory
/// Note: After using queify, pos will be at nullptr. Set pos back to correct location 
/// </summary>
/// <param name="pos"></param>
/// <param name="queue"></param>
void Directory::queify(DirectoryNode* pos, Queue<DirectoryNode>*& queue)
{
	while (pos != nullptr) 
	{
		queue->enqueue(pos);
		add(pos->name);
		pos = pos->next;
	}
}

void Directory::replaceQ(Queue<DirectoryNode>*& queue1, Queue<DirectoryNode>*& queue2)
{
	//Queue<DirectoryNode>* e;
	DirectoryNode* e;
	while (!queue1->empty())
	{
		queue1->dequeue(e);
		queue2->enqueue(e);
	}
}

void Directory::clearq(Queue<DirectoryNode>*& queue)
{
	DirectoryNode* e = nullptr;
	while (!queue->empty())
	{
		queue->enqueue(e);
	}
}



std::string Directory::getPath()
{
	std::string path = "";
	DirectoryNode* elem;
	DirectoryNodeStack<DirectoryNode> emptyStack;
	while (!stack.empty())
	{
		elem = stack.pop();
		emptyStack.push(elem);
	}
	while (!emptyStack.empty())
	{
		elem = emptyStack.pop();
		path += "/" + elem->name;
		stack.push(elem);
	}
	path += "/" + curr->name;
	return path;
}
