#pragma once

#include "OperationOwner.h"
#include "IOutput.h"
#include <math.h>
#include <assert.h>

class QuantizeThreshold : public Base::OperationOwner
{
public:
	QuantizeThreshold(double aQuantizeUnit, double aTreshold = 0.5)
	:
	iQuantizeUnit(aQuantizeUnit)
	{
		assert(aTreshold <= 1.0 && aTreshold >= 0.0);
		this->iTreshold = aTreshold;
	}

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
			int count = int(data[1][i] / iQuantizeUnit);
			double diff = double(data[1][i]) - iQuantizeUnit * count;
			if (count != 0 && std::abs(diff/iQuantizeUnit) >= iTreshold)
			{
				count > 0 ? count++ : count--;
			}
			result[1].Push(count * iQuantizeUnit);
		}
		return result;
	}

	double iQuantizeUnit, iTreshold;
};