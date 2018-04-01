#pragma once

#include "Generator.h"
#include <random>

namespace Generator {

class RandUniform : public Generator
{
public:
	RandUniform(const Sampler& aSampler, double aRange)
		: Generator(aSampler)
		, distribution(-aRange, aRange)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		return Numeric::Number(distribution(generator));
	}

	std::random_device generator{};
	std::uniform_real_distribution<double> distribution;
};

} /* namespace Generator */