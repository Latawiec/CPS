#pragma once

#include "Generator.h"
#include "Sampler.h"
#include "assert.h"
#include <math.h>

struct Triangle : public Base::Generator<double>
{
	Triangle(Base::Sampler aSampler, double aPeriod, double aFill, double aAmplitude = 1.0)
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
			double stage = (value - int(value / iPeriod)*iPeriod);
			double percentStage = stage / iPeriod;
			if (percentStage <= iFill)
			{
				y.push_back( iAmplitude * (percentStage/iFill) );
			}
			else
			{
				y.push_back( iAmplitude - ( iAmplitude * (percentStage-iFill)/(1-iFill)) );
			}
		}

		return Base::Output<double>(x, y);
	}

private:
	double iAmplitude;
	double iFill;
	double iPeriod;
};