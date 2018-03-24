#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include "IOutput.h"

class Histogram : public Base::OperationOwner
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
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 1);
		const Data& data = aData[0]->GetOutput();

		//Zrobimy to dla jednej osi danych bo mi się nie chce. Jeśli ktoś poda więcej to wywali.
		assert(data.Size() == 2);

		auto sortedValues = data[1].GetRaw();

		//To może ostro nie działać dla zespolonych liczb xD ale co tam!
		std::sort(sortedValues.begin(), sortedValues.end());

		//TODO: Histogram xD

		//Kopiujemy pierwsze dane.
		Data result{};
		result.Push(data[0]);
		result.Push(Base::Array(data[0].Size()));

		return result;
	}

};