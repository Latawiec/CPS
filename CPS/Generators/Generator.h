#pragma once

#include "Containers.h"
#include "IOutput.h"
#include "Sampler.h"

namespace Generator {

class Generator : public Base::IOutput
{
public:
	Generator(const Sampler& aSampler)
	{
		data.Push(aSampler.Get());
	}

	Generator() = default;

	virtual ~Generator() = default;

	const Base::Data& GetOutput() const override
	{
		return data;
	}

	virtual Generator& Generate()
	{
		data.Push(Base::Array(data[0].Size()));
		for (unsigned int i = 0; i < data[0].Size(); ++i)
		{
			data[1].Push(GeneratorFunction(data[0][i]));
		}
		return *this;
	}

protected:
	virtual Numeric::Number GeneratorFunction(const Numeric::Number& aArg) = 0;

	Base::Data	   data;
};

} /* namespace Generator */