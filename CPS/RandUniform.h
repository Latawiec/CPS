#pragma once

#include "Generator.h"
#include <random>

class RandUniform : public Generator
{
public:
	RandUniform(const Sampler& aSampler, double aRange)
		: Generator(aSampler)
		, range(aRange)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		std::random_device generator{};
		std::uniform_real_distribution<double> distribution(-range, range);

		return Numeric::Number(distribution(generator));
	}

	double range;
};