#pragma once

#include "OperationOwner.h"
#include "IOutput.h"
#include <assert.h>

class QuantizeCut : public Base::OperationOwner
{
public:
	QuantizeCut(double aQuantizeUnit)
	:
	iQuantizeUnit(aQuantizeUnit)
	{}

private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		assert(aData.size() == 1);

		//Kopiujemy pierwsze dane.
		const Data& data = aData[0]->GetOutput();

		Data result = {};
		result.Push(data[0]);
		result.Push(Base::Array{});
		//Dodajemy każdy kolejny do skopiowanego...
		for (uint32_t i = 0; i < data[0].Size(); ++i)
		{
			result[1].Push(int(data[1][i]/iQuantizeUnit) * iQuantizeUnit);
		}
		return result;
	}

	double iQuantizeUnit;
};