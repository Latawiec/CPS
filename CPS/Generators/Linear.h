#pragma once

#include <math.h>
#include "Generator.h"

namespace Generator {

class Linear : public Generator
{
public:
	Linear(const Sampler& aSampler, Numeric::Number aIncrease = 1.0, Numeric::Number aStartValue = 0.0, Numeric::Number aOffset = 0.0)
		: Generator(aSampler)
		, increase(aIncrease)
		, start(aStartValue)
		, offset(aOffset)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		return start + increase*( aArg + offset);
	}

	Numeric::Number increase, start, offset;
};

} /* namespace Generator */