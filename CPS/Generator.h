#pragma once

#include "Containers.h"
#include "Sampler.h"

class Generator
{
public:
	Generator(const Sampler& aSampler)
	{
		data.Push(aSampler.Get());
	}

	virtual ~Generator() = default;

	const Base::Data& Get()
	{
		if (!generated)
		{
			Initialize();
		}
		return data;
	}

protected:
	virtual Numeric::Number GeneratorFunction(const Numeric::Number& aArg) = 0;


private:
	void Initialize()
	{
		data.Push(Base::Array(data[0].Size()));
		for (unsigned int i = 0; i < data[0].Size(); ++i)
		{
			data[1].Push(GeneratorFunction(data[0][i]));
		}
		generated = true;
	}

	bool		   generated = false;
	Base::Data	   data;
};