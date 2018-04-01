#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include "IOutput.h"

namespace Operation {

class Histogram : public OperationOwner
{
public:
	Histogram(Numeric::Number aFrequency = 1.0, uint32_t aFirstIndex = 0, uint32_t aLastIndex = 0)
		: frequency(aFrequency)
		, firstIndex(aFirstIndex)
		, lastIndex(aLastIndex)
	{}

private:
	uint32_t firstIndex, lastIndex;
	Numeric::Number frequency;
	Base::Data OperationDefinition(std::vector<const Base::IOutput*> aData) override
	{
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 1);
		const Data& data = aData[0]->GetOutput();

		//Zrobimy to dla jednej osi danych bo mi się nie chce. Jeśli ktoś poda więcej to wywali.
		assert(data.Size() == 2);

		if (0 == lastIndex)
		{
			lastIndex = data[1].Size();
		}

		auto sortedValues = std::vector<Numeric::Number>(data[1].GetRaw().begin() + firstIndex, data[1].GetRaw().begin() + lastIndex - 1);

		//To może ostro nie działać dla zespolonych liczb xD ale co tam!
		std::sort(sortedValues.begin(), sortedValues.end());

		int32_t minValueDivs = int32_t(double(sortedValues.front()) / frequency);
		minValueDivs = minValueDivs <= 0 ? minValueDivs - 1 : minValueDivs + 1;

		double smallestValue = minValueDivs*frequency;
		minValueDivs = minValueDivs <= 0 ? -minValueDivs : minValueDivs;

		int32_t maxValueDivs = int32_t(double(sortedValues.back()) / frequency);
		maxValueDivs = maxValueDivs <= 0 ? -maxValueDivs : maxValueDivs;
		maxValueDivs += 1;

		Data result{};
		result.Push(Base::Array(minValueDivs + maxValueDivs));

		for (uint32_t i = 0; i < minValueDivs + maxValueDivs; ++i)
		{
			result[0].Push(i*frequency + smallestValue);
		}

		result.Push(Base::Array(minValueDivs + maxValueDivs, 0.0));
		{
			uint32_t i = 0;
			for (double value : sortedValues)
			{
				while (value > (i+1)*frequency + smallestValue)
				{
					i++;
				}
				result[1][i] += 1;
			}
		}
		return result;
	}

};

} /* namespace Operation */