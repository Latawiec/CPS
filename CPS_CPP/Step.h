#pragma once

#include "Generator.h"
#include "Sampler.h"
#include "assert.h"
#include <math.h>

struct Step : public Base::Generator<double>
{
	Step(Base::Sampler aSampler, double aStepValue, double aAmplitude = 1.0)
		: iAmplitude(aAmplitude)
		, iStepValue(aStepValue)
		, Generator(aSampler)
	{}

	Base::Output<double> GeneratorDefinition(Base::Sampler& aSampler)
	{
		std::vector<double> x = aSampler.Generate();
		std::vector<double>	y;

		y.reserve(x.size());

		for (const auto& value : x)
		{
			if (value == iStepValue)
			{
				y.push_back(0.5*iAmplitude);
			}
			else if (value > iStepValue)
			{
				y.push_back(iAmplitude);
			} 
			else
			{
				y.push_back(0);
			}
		}

		return Base::Output<double>(x, y);
	}

private:
	double iAmplitude;
	double iStepValue;
	double iPeriod;
};