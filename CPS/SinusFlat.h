#pragma once

#include <math.h>
#include "Generator.h"

class SinFlat : public Generator
{
public:
	SinFlat(const Sampler& aSampler, double aAmplitude = 1.0, double aOffset = 0.0)
		: Generator(aSampler)
		, amplitude(aAmplitude)
		, offset(aOffset)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		double sinValue = std::sin(double(aArg) + offset);
		return sinValue >= 0 ? amplitude*sinValue : 0.0;
	}

	double amplitude, offset;
};