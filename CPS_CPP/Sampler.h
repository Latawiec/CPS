#pragma once

namespace Base {

struct Sampler
{
	Sampler(double offset, double frequency)
		:
		iOffset(offset),
		iCurrent(offset),
		iFrequency(frequency)
	{}

	void Reset()
	{
		iCurrent = iOffset;
	}

	double Next()
	{
		iCurrent += iFrequency;
		return iCurrent;
	}

	double Current()
	{
		return iCurrent;
	}

private:
	double					 iOffset;
	double					 iFrequency;
	double					 iCurrent = 0;
};

}