#pragma once

#include <random>
#include "Generator.h"

class ImpulseNoise : public Generator
{
public:
	ImpulseNoise(const Sampler& aSampler, double aProbability, Numeric::Number aAmplitude = 1.0)
		: Generator(aSampler)
		, probability(aProbability)
		, amplitude(aAmplitude)
		, distribution(0.0, 1.0)
	{}

protected:
	Numeric::Number GeneratorFunction(const Numeric::Number& aArg) override
	{
		double value = distribution(generator);
		if(value <= probability)
		{
			return amplitude;
		}
		else
		{
			return 0.0;
		}
	}
	std::uniform_real_distribution<double> distribution;
	std::random_device					   generator{};
	Numeric::Number						   amplitude;
	double								   probability;
};