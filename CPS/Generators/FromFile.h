#pragma once

#include "Generator.h"
#include <fstream>

namespace Generator {

class FromFile : public Generator
{
public:
	FromFile(const std::string& aFilename)
		: Generator()
		, fileName(aFilename){}

	Generator& Generate() override
	{
		std::string  line;
		std::fstream file;
		file.open(fileName, std::fstream::in);
		if (file.is_open())
		{
			char	 holder = 0;
			uint16_t arrayCount = 0;
			double	 value;

			file >> holder;
			assert(holder == '{');

			while (file.good())
			{
				while (holder != '[' && file.good())
				{
					file >> holder;
				}
				if (!file.good())
				{
					break;
				}
				data.Push(Base::Array());

				while (holder != ']')
				{
					file >> value;
					file >> holder;
					data[arrayCount].Push(value);
				}
				arrayCount++;
			}
			file.close();
		}
		else
		{
			throw std::runtime_error("Cannot open file.");
		}
		return *this;
	}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override { return 0.0; }

	std::string		fileName;
	uint32_t		counter = 0, impulse;
};

} /* namespace Generator */