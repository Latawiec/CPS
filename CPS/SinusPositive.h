#pragma once

#include <math.h>
#include "Generator.h"

class SinPositive : public Generator
{
public:
	SinPositive(const Sampler& aSampler, double aAmplitude = 1.0, double aOffset = 0.0)
		: Generator(aSampler)
		, amplitude(aAmplitude)
		, offset(aOffset)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		double value = amplitude*std::sin(double(aArg) + offset);
		return value >= 0 ? value : -value;
	}

	double amplitude, offset;
};