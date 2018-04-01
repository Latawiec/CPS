#pragma once

#include <math.h>
#include "Generator.h"

namespace Generator {

class SinFlat : public Generator
{
public:
	SinFlat(const Sampler& aSampler, double aPeriod = 6.283185307179586476925286766559, double aAmplitude = 1.0, double aOffset = 0.0)
		: Generator(aSampler)
		, frequency(1.0/aPeriod)
		, amplitude(aAmplitude)
		, offset(aOffset)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		double sinValue = std::sin( frequency*(double(aArg) + offset) );
		return sinValue >= 0 ? amplitude*sinValue : 0.0;
	}

	double frequency, amplitude, offset;
};

} /* namespace Generator */