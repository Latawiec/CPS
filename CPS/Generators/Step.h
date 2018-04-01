#pragma once

#include <math.h>
#include "Generator.h"

namespace Generator {

class Step : public Generator
{
public:
	Step(const Sampler& aSampler, Numeric::Number aStep, Numeric::Number aAmplitude = 1.0, Numeric::Number aOffset = 0.0)
		: Generator(aSampler)
		, step(aStep)
		, amplitude(aAmplitude)
		, offset(aOffset)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		if (aArg + offset > step)
		{
			return amplitude;
		}
		else if(aArg + offset == step)
		{
			return amplitude*0.5;
		}
		else
		{
			return 0.0;
		}
	}

	Numeric::Number step, amplitude, offset;

};

} /* namespace Generator */