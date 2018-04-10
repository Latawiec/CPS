#pragma once

#include <math.h>
#include "Generator.h"

class SinPositive : public Generator
{
public:
	SinPositive(const Sampler& aSampler, double aPeriod = 6.283185307179586476925286766559, double aAmplitude = 1.0, double aOffset = 0.0)
		: Generator(aSampler)
		, frequency(1.0/aPeriod)
		, amplitude(aAmplitude)
		, offset(aOffset)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		double value = amplitude*std::sin( frequency*(double(aArg) + offset) );
		return value >= 0 ? value : -value;
	}

	double frequency, amplitude, offset;
};