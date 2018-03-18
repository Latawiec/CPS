#pragma once

#include "Generator.h"
#include "Sampler.h"
#include  <random>

struct RandomNormalDistribution : public Base::Generator<double>
{
	RandomNormalDistribution(Base::Sampler aSampler)
		: Generator(aSampler)
	{}

	Base::Output<double> GeneratorDefinition(Base::Sampler& aSampler) override
	{
		std::default_random_engine generator;
		std::normal_distribution<double> distribution(0, 1);

		std::vector<double> x = aSampler.Generate();
		std::vector<double>	y;

		y.reserve(x.size());

		for (const auto& value : x)
		{
			y.push_back(distribution(generator));
		}

		return Base::Output<double>(x, y);
	}
};