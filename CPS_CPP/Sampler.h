#pragma once

#include <vector>

namespace Base {

struct Sampler
{
	Sampler(double offset, double frequency, int count)
		:
		iOffset(offset),
		iCurrent(offset),
		iFrequency(frequency),
		iCount(count)
	{}

	const std::vector<double>& Generate()
	{
		if (!iCalculated)
		{
			iResult.reserve(iCount);
			for (int i = 0; i < iCount; ++i)
			{
				iResult.push_back(iOffset + i*iFrequency);
			}
			iCalculated = true;
		}
		return iResult;
	}

private:
	double					 iOffset;
	double					 iFrequency;
	int						 iCount = 0;
	double					 iCurrent = 0;
	bool					 iCalculated = false;
	std::vector<double>		 iResult;
};

}