#pragma once

#include "Generator.h"
#include "Sampler.h"

struct BasicGenerator : public Base::Generator<double>
{
	BasicGenerator(double aIncrease, double aLimit, double aFrequency, double aOffset = 0)
		: Generator(Base::Sampler(aOffset, aFrequency))
		, iLimit(aLimit)
		, iIncrease(aIncrease)
	{}

	Base::Output<double> GeneratorDefinition(Base::Sampler& aSampler) override
	{
		Base::Output<double> out;
		aSampler.Reset();

		while (aSampler.Next() <= iLimit)
		{
			out.PushValue(aSampler.Current(), aSampler.Current()*iIncrease);
		}

		return out;
	}

private:
	double iLimit;
	double iIncrease;
};