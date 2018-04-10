#pragma once


#include "Generator.h"

class Impulse : public Generator
{
public:
	Impulse(const Sampler& aSampler, uint32_t aImpulse, Numeric::Number aAmplitude = 1.0)
		: Generator(aSampler)
		, impulse(aImpulse)
		, amplitude(aAmplitude)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		if (impulse == counter)
		{
			counter++;
			return amplitude;
		}
		else
		{
			counter++;
			return 0.0;
		}
	}

	Numeric::Number	amplitude;
	uint32_t		counter = 0, impulse;
};