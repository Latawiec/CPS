#pragma once

#include <math.h>
#include "Generator.h"

class Sin : public Generator
{
public:
	Sin(const Sampler& aSampler)
	:
	Generator(aSampler)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		return std::sin(aArg);
	}
};