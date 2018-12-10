#include <iostream>
#include <string>
#include <ctime>

#include "insertion_map.h"

int main()
{
	insertion_map<std::string, uint32_t> stringDoubleMap;
	stringDoubleMap.insert(std::make_pair("zz", 4));
	stringDoubleMap.insert(std::make_pair("yy", 5));
	stringDoubleMap.insert(std::make_pair("KKK", 6));
	stringDoubleMap.insert(std::make_pair("zzz", 9));
	stringDoubleMap.insert(std::make_pair("l", 4));
	stringDoubleMap.insert(std::make_pair("h", 4));
	stringDoubleMap.insert(std::make_pair("b", 4));

	std::srand((unsigned int)std::time(nullptr)); // use current time as seed for random generator
	for (uint32_t testNum = 0; testNum < 50000000; testNum++)
	{
		if (testNum % 1000000 == 0)
			std::cout << testNum << " - ";
		stringDoubleMap.insert(std::make_pair(std::to_string(testNum), (uint32_t)std::rand()));
	}

	stringDoubleMap.insert("k", 11);
	stringDoubleMap.insert("b", 33);
	stringDoubleMap.insert("pp", 69);

	stringDoubleMap["haha"] = 2;
	stringDoubleMap["hahaha"] = 33;

	if (!stringDoubleMap.empty())
	{
		for (insertion_map<std::string, uint32_t>::iterator it = stringDoubleMap.begin(); it != stringDoubleMap.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
	}

	std::cout << std::endl << "Accessing with square bracket operator of pp: " << stringDoubleMap["pp"] << std::endl;

	stringDoubleMap["pp"] = 89;
	std::cout << std::endl << "Accessing with square bracket operator of edited pp: " << stringDoubleMap["pp"] << std::endl;

	std::getchar();

	return 0;
}