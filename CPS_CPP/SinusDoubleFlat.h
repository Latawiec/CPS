#pragma once

#include "Generator.h"
#include "Sampler.h"
#include "assert.h"
#include <math.h>

struct SinDoubleFlat : public Base::Generator<double>
{
	SinDoubleFlat(Base::Sampler aSampler, double aAmplitude = 1.0)
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
			double sinVal = iAmplitude*std::sin(value);
			if (sinVal > 0)
			{
				y.push_back(sinVal);
			}
			else
			{
				y.push_back(-sinVal);
			}
		}

		return Base::Output<double>(x, y);
	}

private:
	double iAmplitude;
};