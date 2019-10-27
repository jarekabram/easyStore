#include <iostream>
#include <thread>
#include "ThreadManager.h"
#include <string>
#include <memory>
#include <functional>
#include "FileManager.h"
#include "Utils.h"

void printMenu() 
{
	std::cout << "Welcome to easyStore, please choose an option:\n" <<
		"1. new		- creation of new file\n" <<
		"2. print		- shows the names of files\n" <<
		"3. quit/exit	- exiting program\n";
}

int main()
{
	ThreadManager threadManager;
	std::shared_ptr<FileManager> fileManager = std::make_shared<FileManager>();
	std::string command;
	
	while ( true )
	{
		printMenu();
		std::getline(std::cin, command);
		if (command == "new")
		{
			std::string path, content;
			std::cout << "Please insert name of file which should be created:	\n";
			std::getline(std::cin, path);

			// first check if file extension is for instance txt, log or xml
			if (Utils::validateExtension(path))
			{
				std::cout << "Please type in the text which you would store in file:	\n";
				std::getline(std::cin, content);
				threadManager.runTask(std::bind(&FileManager::prepareFile, fileManager.get(), path, content));
			}
			else 
			{
				std::cout << "File extension is different than: txt, log or xml. Try again.\n";
			}
		}
		else if (command == "print")
		{
			threadManager.runTask(std::bind(&FileManager::showAvailableFiles, fileManager.get()));
		}
		else if (command == "quit" || command == "exit")
		{
			exit(0);
		}
		else
		{
			std::cout << "No such command please try again\n";
		}
	}

	return 0;
}
