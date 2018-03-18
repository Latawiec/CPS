#pragma once

#include "Generator.h"
#include "Sampler.h"
#include "assert.h"
#include <math.h>

struct Square : public Base::Generator<double>
{
	Square(Base::Sampler aSampler, double aPeriod, double aFill, double aAmplitude = 1.0)
		: iAmplitude(aAmplitude)
		, iFill(aFill)
		, iPeriod(aPeriod)
		, Generator(aSampler)
	{}

	Base::Output<double> GeneratorDefinition(Base::Sampler& aSampler)
	{
		std::vector<double> x = aSampler.Generate();
		std::vector<double>	y;

		y.reserve(x.size());

		for (const auto& value : x)
		{
			if( (value - int(value/iPeriod)*iPeriod) <  iPeriod*iFill )
			{
				y.push_back(iAmplitude);
			}
			else
			{
				y.push_back(-iAmplitude);
			}
		}

		return Base::Output<double>(x, y);
	}

private:
	double iAmplitude;
	double iFill;
	double iPeriod;
};