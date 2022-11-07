#include "Directory.h"
#include <iostream>


//Can probably clean up node structure got messy while debugging

void toUpper(std::string& e)
{
	for (int i = 0; i < e.length(); i++)
	{
		if (e[i] >= 97 && e[i] <= 122)
		{
			e[i] -= 32;
		}
	}
}

bool handleMovement(Directory& dir)
{
	std::string input;
	std::cout <<"[" <<  dir.getPath() << "] ";
	std::getline(std::cin, input);
	toUpper(input);
	std::size_t pos = input.find(" ");

	if (input.substr(0, pos) == "EXIT")
	{
		return false;
	}
	if (input.substr(0, pos) == "MAKE")
	{
		dir.add(input.substr(pos + 1));
		return true;
	}
	if (input.substr(0, pos) == "LIST")
	{
		dir.listDirectories();
		return true;
	}
	if (input.substr(0, pos) == "GOTO")
	{
		if (input.substr(pos + 1) == "ROOT")
		{
			dir.gotoRoot();
			return true;
		}
		dir.gotoDir(input.substr(pos + 1));
		return true;
	}
	if (input.substr(0, pos) == "GOUP")
	{
		dir.goup();
		return true;
	}
	if (input.substr(0, pos) == "CLONE")
	{
		//std::cout << "Follow this format for use: CLONE [absolute path to directory you'd like it cloned to] i.e. CLONE"
		//				" /ROOT/USERS/AUSTIN\n";
		dir.clone(input.substr(pos + 1));
		return true;
	}
	if (input.substr(0, pos) == "PWD")
	{
		std::cout << dir.getPath() << std::endl;
		return true;
	}
	if (input.substr(0, pos) == "DEL")
	{
		std::cout << "Are you certain you'd like to delete [" << dir.getPath() << "/" << input.substr(pos + 1) << "] ? (Y/N)";
		std::string choice;
		std::cin >> choice;
		toUpper(choice);
		if (choice == "Y")
		{
			dir.deleteDir(input.substr(pos + 1));
		}
		std::cin.ignore();
		return true;
	}
}


int main()
{
	Directory newDir;
	while (handleMovement(newDir))
	{
		
	}
}