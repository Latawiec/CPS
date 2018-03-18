#pragma once

#include "Generator.h"
#include "Sampler.h"
#include  <random>

struct RandomUniformDistribution : public Base::Generator<double>
{
	RandomUniformDistribution(Base::Sampler aSampler, double aAmplitude)
		: Generator(aSampler)
		, iAmplitude(aAmplitude)
	{}

	Base::Output<double> GeneratorDefinition(Base::Sampler& aSampler) override
	{
		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution(-iAmplitude, iAmplitude);

		std::vector<double> x = aSampler.Generate();
		std::vector<double>	y;

		y.reserve(x.size());

		for (const auto& value : x)
		{
			y.push_back(distribution(generator));
		}

		return Base::Output<double>(x, y);
	}

private:
	double iAmplitude;
};