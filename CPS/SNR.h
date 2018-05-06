#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include "IOutput.h"

class SNR : public Base::OperationOwner
{
public:
	SNR() = default;
private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 2);

		const Data& data = aData[0]->GetOutput();
		const Data& values = aData[1]->GetOutput();
		Number bottom = 0.0;
		Number top = 0.0;

		//Zrobimy to dla jednej osi danych bo mi się nie chce. Jeśli ktoś poda więcej to wywali.
		assert(data.Size() == 2);

		for (int i = 0; i < data[1].Size(); ++i)
		{
			double temp = data[1][i] - values[1][i];
			bottom += temp*temp;
			top += data[1][i] * data[1][i];
		}

		double SNR = 10.0 * std::log10(top/bottom);

		Data result{};
		result.Push(data[0]);
		result.Push({});

		for (int i = 0; i < data[1].Size(); ++i)
		{
			result[1].Push(SNR);
		}

		return result;
	}

};