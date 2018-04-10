#pragma once

#include <math.h>
#include "Generator.h"

class Square : public Generator
{
public:
	Square(const Sampler& aSampler, double aFill, double aPeriod, double aAmplitude = 1.0, double aOffset = 0.0)
		: Generator(aSampler)
		, fill(aFill)
		, period(aPeriod)
		, amplitude(aAmplitude)
		, offset(aOffset)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		double arg = (double)aArg + offset;
		double percentStage = (arg - int(arg / period)*period) / period;
		if (percentStage <= fill)
		{
			return amplitude;
		}
		else
		{
			return -amplitude;
		}
	}

	double fill, period, amplitude, offset;
};