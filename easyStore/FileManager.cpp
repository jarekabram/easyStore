#include <iostream>
#include <chrono>
#include <fstream>
#include "ThreadManager.h"
#include "FileManager.h"

bool FileManager::prepareFile(std::string p_path, std::string p_content)
{
	m_mutex.lock();
	// create new file
	std::ofstream myfile;
	myfile.open(p_path);
	if (myfile.bad()) 
	{
		m_mutex.unlock();
		return false;
	}
	// just for simulation
	std::this_thread::sleep_for(std::chrono::seconds(5));
	myfile << p_content;
	myfile.close();
	// file succesfully created, add it to list
	m_availableFiles.emplace_back(p_path);
	
	m_mutex.unlock();
	return true;
}

void FileManager::showAvailableFiles()
{
	m_mutex.lock();
	std::cout << "Available files: " << std::endl;

	if (m_availableFiles.empty()) 
	{
		std::cout << "There was no file created during program is running, I'm sorry." << std::endl;
	}
	else 
	{
		for (auto file : m_availableFiles)
		{
			std::cout << file << std::endl;
		}
	}
	// just for simulation
	std::this_thread::sleep_for(std::chrono::seconds(5));
	m_mutex.unlock();
}
