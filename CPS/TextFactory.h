#pragma once

#include <vector>
#include <memory>
#include "IOutput.h"
#include "InputParser.h"
#include "Sampler.h"

#include "SamplerCreator.h"
#include "SinCreator.h"

class TextFactory
{
public:
	void Create(const std::string& aType)
	{
		//samplers
		if (aType == "sampler") { samplers.push_back(SamplerCreator::Create()); }
		else if(aType == "generator")
		{
			if (samplers.empty())
			{
				std::cout << "No Sampler is defined. Cannot create a generator!\n";
				return;
			}
			//generators
			uint32_t samplerID = 0;
			std::cout << "Put sampler ID (" << samplerID << "): ";
			InputParser::Get(samplerID);
			if (samplerID > samplers.size())
			{
				std::cout << "No sampler is defined. Cannot create Generator!\n";
				return;
			}
			const Sampler& sampler = *samplers[samplerID];

			std::cout << "Sepcify function to be generated: ";
			std::string function = "";
			InputParser::Get(function);
			if (function == "sin") { cache.push_back(SinCreator::Create(sampler)); }
			else if (function == "line") {}
			else { std::cout << "Aborting! No known name specified.\n"; }
		}
		else if (aType == "operation")
		{
			if (cache.empty())
			{
				std::cout << "No data for the operation.\n";
				return;
			}

			std::cout << "Sepcify operation to be performed: ";
			std::string function = "";
			InputParser::Get(function);
			
		}
	}

protected:

private:
	std::vector<const std::unique_ptr<IOutput>> cache;
	std::vector<const std::unique_ptr<Sampler>> samplers;
};