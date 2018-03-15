#pragma once

#include "Output.h"
#include "Sampler.h"

namespace Base {

template<class T>
struct Generator : public Output<T>
{
	Generator(Sampler aSampler)
		: iSampler(std::move(aSampler))
	{}

	virtual ~Generator() = default;

	Generator<T>& Execute()
	{
		static_cast<Output<T>&>(*this) = GeneratorDefinition(iSampler);
		return *this;
	}

protected:
	virtual Output<T> GeneratorDefinition(Sampler& aSampler) = 0;

	Sampler iSampler;
};

}