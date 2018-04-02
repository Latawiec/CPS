#pragma once

#include <iostream>
#include <sstream>
#include <string>

class InputParser
{
public:
	template<class T>
	static void Get(T& aValue)
	{
		while (getline(std::cin, in))
		{
			if (!in.empty())
			{
				std::stringstream s(in);
				if (!(s >> aValue))
				{
					std::cout << "Invalid input.";
				}
				else
				{
					break;
				}
			}
		}
	}
private:
	std::string in = "";
};