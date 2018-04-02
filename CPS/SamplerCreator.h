#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "InputParser.h"
#include "Sampler.h"

class SamplerCreator
{
public:
	static std::unique_ptr<Sampler> Create()
	{
		double offset = 0;
		double interval = 0.1;
		double limit = 10;
		
		std::cout << "Set sampler offset (" << offset << "): ";
		InputParser::Get(offset);
		std::cout << "Set sampler interval (" << interval << "): ";
		InputParser::Get(interval);
		std::cout << "Set sampler limit (" << limit << "): ";
		InputParser::Get(limit);

		return std::unique_ptr<Sampler>(new Sampler(offset, interval, limit));
	}
};