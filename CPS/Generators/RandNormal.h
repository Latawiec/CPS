#pragma once

#include <random>
#include "Generator.h"

namespace Generator {

class RandNormal : public Generator
{
public:
	RandNormal(const Sampler& aSampler)
		: Generator(aSampler)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		std::random_device generator{};
		std::normal_distribution<double> distribution(0, 1);

		return Numeric::Number(distribution(generator));
	}
};

} /* namespace Generator */