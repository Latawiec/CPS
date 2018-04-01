#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include "IOutput.h"

namespace Operation {

class RMS : public OperationOwner
{
public:
	RMS(uint32_t aFirstIndex = 0, uint32_t aLastIndex = 0)
		: firstIndex(aFirstIndex)
		, lastIndex(aLastIndex)
	{}

private:
	uint32_t firstIndex, lastIndex;
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 1);

		const Data& data = aData[0]->GetOutput();
		Number rmsValue = 0.0;

		//Zrobimy to dla jednej osi danych bo mi się nie chce. Jeśli ktoś poda więcej to wywali.
		assert(data.Size() == 2);

		for (int i = 0; i < data[1].Size(); ++i)
		{
			rmsValue += data[1][i]*data[1][i];
		}

		if (lastIndex == 0)
		{
			lastIndex = data[1].Size();
		}
		rmsValue /= (lastIndex - firstIndex + 1);

		double rms = std::sqrt(rmsValue);

		//Kopiujemy pierwsze dane.
		Data result{};
		result.Push(data[0]);
		result.Push(Base::Array(data[0].Size()));

		for (int i = 0; i < data[1].Size(); ++i)
		{
			result[1].Push(rms);
		}

		return result;
	}

};

} /* namespace Operation */