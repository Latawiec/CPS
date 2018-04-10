#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <random>
#include <fstream>

class ToFile : public Base::IOperation
{
public:
	ToFile(const std::string& aName = "", const std::string& aType = "")
		: iFilename(aName)
		, iGraphType(aType)
	{}

	virtual IOperation& AddInput(const IOutput& aData)
	{
		iOutput = &aData;
		return *this;
	}
	virtual IOperation& RemoveInput(const IOutput& aData)
	{
		if (&aData == iOutput)
		{
			iOutput = nullptr;
		}
		return *this;
	}

	virtual IOperation& Execute()
	{
		if (!iOutput)
		{
			throw std::runtime_error("No data was passed to the ToFile operation!");
		}
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);

		std::random_device generator{};
		std::uniform_int_distribution<int> distribution(-10000, 10000);
		int value = distribution(generator);

		std::stringstream ss;
		ss << "../QuickDisplay/data/";
		ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%OH-%OM-%OS");
		if (iFilename.empty())
		{
			ss << "_" << value;
		}
		else
		{
			ss << '_' << iFilename;
		}
		ss << ".json";

		std::fstream file;
		file.open(ss.str(), std::fstream::out);
		if (file.is_open())
		{
			file << '{' << '\n';
			file << iOutput->GetOutput() << '\n';
			if (!iGraphType.empty())
			{
				file << "\"type\": \"" << iGraphType << "\"," << '\n';
			}
			else
			{
				file << "\"type\": \"scatter\"," << '\n';
			}

			if (!iFilename.empty())
			{
				file << "\"name\": \"" << iFilename << "\"\n";
			}
			else
			{
				file << "\"name\": \"" << std::put_time(std::localtime(&in_time_t), "%Y - %m - %d_%OS") << "\"\n";
			}
			ss << "_" << value;
			file << '}';

			file.close();
		}
		else
		{
			throw std::runtime_error("Cannot open file.");
		}
	}

private:
	const IOutput*	iOutput = nullptr;
	std::string		iFilename;
	std::string		iGraphType;
};