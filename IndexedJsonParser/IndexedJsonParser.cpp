// IndexedJsonParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "JSON.h"
int main()
{

	
	std::ifstream ifs("./8bit.json",std::ios::ate);
	size_t fileSize = ifs.tellg();
	ifs.seekg(std::ios::beg);
	std::string json = std::string(fileSize, ' ');
	ifs.read((char *)json.data(), fileSize);
	std::cout << "IndexedJsonParser Parsing..." << std::endl;
	JSON index(json);
	std::cout << "Done!" << std::endl;
	std::cout << "Json is " << fileSize << " bytes long" << std::endl;

	size_t size = 0;
	/*for (auto & entry : index.m_index) {
		size += sizeof(entry);
		size += entry.second.Children.size() * sizeof(uint32_t);
	}*/
	std::cout << "Map is " << size << " bytes long";
	std::cin >> json;
}
