#pragma once

#include "Generator.h"
#include "Sampler.h"
#include "assert.h"
#include <math.h>

struct SinFlat : public Base::Generator<double>
{
	SinFlat(Base::Sampler aSampler, double aAmplitude = 1.0)
		:
		iAmplitude(aAmplitude),
		Generator(aSampler)
	{}

	Base::Output<double> GeneratorDefinition(Base::Sampler& aSampler)
	{
		std::vector<double> x = aSampler.Generate();
		std::vector<double>	y;

		y.reserve(x.size());

		for (const auto& value : x)
		{
			double sinVal = std::sin(value);
			if (sinVal > 0)
			{
				y.push_back(iAmplitude*sinVal);
			}
			else
			{
				y.push_back(0.0);
			}
		}

		return Base::Output<double>(x, y);
	}

private:
	double iAmplitude;
};