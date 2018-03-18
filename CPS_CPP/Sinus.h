﻿#pragma once

#include "Generator.h"
#include "Sampler.h"
#include "assert.h"
#include <math.h>

struct Sin : public Base::Generator<double>
{
	Sin(Base::Sampler aSampler, double aAmplitude = 1.0)
		:
		iAmplitude(aAmplitude),
		Generator(aSampler)
	{}

	Base::Output<double> GeneratorDefinition(Base::Sampler& aSampler)
	{
		std::vector<double> x = aSampler.Generate();
		std::vector<double>	y;

		y.reserve(x.size());

		for (const auto& value : x)
		{
			y.push_back(std::sin(value));
		}

		return Base::Output<double>(x, y);
	}

private:
	double iAmplitude;
};