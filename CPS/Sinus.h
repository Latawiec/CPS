#pragma once

#include <math.h>
#include "Generator.h"

class Sin : public Generator
{
public:
	Sin(const Sampler& aSampler, double aPeriod = 1.0,  double aAmplitude = 1.0, double aOffset = 0.0)
	: Generator(aSampler)
	, period(aPeriod)
	, amplitude(aAmplitude)
	, offset(aOffset)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		return amplitude*std::sin( ((double(aArg) + offset)/period)*6.283185307179586476925286766559);
	}

	double period, amplitude, offset;
};