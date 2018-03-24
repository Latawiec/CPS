#pragma once

#include <math.h>
#include "Generator.h"

class Sin : public Generator
{
public:
	Sin(const Sampler& aSampler, double aPeriod = 6.283185307179586476925286766559,  double aAmplitude = 1.0, double aOffset = 0.0)
	: Generator(aSampler)
	, frequency(1.0/aPeriod)
	, amplitude(aAmplitude)
	, offset(aOffset)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		return amplitude*std::sin( frequency*(double(aArg) + offset) );
	}

	double frequency, amplitude, offset;
};