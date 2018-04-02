#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "InputParser.h"
#include "Sinus.h"

class SinCreator
{
public:

	static std::unique_ptr<IOutput> Create(const Sampler& aSampler)
	{
		uint32_t samplerId = 100000000; //a big number.
		std::string in = "";
		double period = 6.283185307179586476925286766559;
		double amplitude = 1.0;
		double offset = 0.0;

		std::cout << "Period (" << period << "): ";
		InputParser::Get(period);
		std::cout << "Amplitude (" << amplitude << "): ";
		InputParser::Get(amplitude);
		std::cout << "Offset (" << offset << "): ";
		InputParser::Get(offset);

		return std::unique_ptr<IOutput>(new Sin(aSampler, period, amplitude, offset));
	}
};