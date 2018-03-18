#pragma once

#include "Generator.h"
#include "Sampler.h"

struct Linear : public Base::Generator<double>
{
	Linear(Base::Sampler aSampler, double aIncrease, double aOffset = 0.0)
		: Generator(aSampler)
		, iIncrease(aIncrease)
		, iOffset(aOffset)
	{}

	Base::Output<double> GeneratorDefinition(Base::Sampler& aSampler) override
	{
		std::vector<double> x = aSampler.Generate();
		std::vector<double>	y;

		y.reserve(x.size());

		for (const auto& value : x)
		{
			y.push_back(iIncrease*value + iOffset);
		}

		return Base::Output<double>(x, y);
	}

private:
	double iIncrease;
	double iOffset;
};