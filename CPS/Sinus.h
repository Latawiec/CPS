#pragma once

#include <math.h>
#include "Generator.h"

class Sin : public Generator
{
public:
	Sin(const Sampler& aSampler, double aAmplitude = 1.0, double aOffset = 0.0)
	: Generator(aSampler)
	, amplitude(aAmplitude)
	, offset(aOffset)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		return amplitude*std::sin( double(aArg) + offset);
	}

	double amplitude, offset;
};