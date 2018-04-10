#pragma once

#include "Containers.h"

class Sampler
{
public:
	Sampler(double aOffset, double aInterval, double aLimit)
	: offset(aOffset)
	, interval(aInterval)
	, limit(aLimit)
	, data( (aLimit-aOffset) / aInterval )
	{
		Initialize();
	}

	const Base::Array& Get() const
	{
		return data;
	}

private:
	void Initialize()
	{
		if (offset >= limit) {
			throw std::runtime_error("You just wanted to create an empty array using this Sampler. Really?...");
		}

		double value = offset;
		while (value <= limit)
		{
			data.Push(value);
			value += interval;
		}
	}

	double offset, interval, limit;
	Base::Array data;
};