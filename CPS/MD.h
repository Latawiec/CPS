#pragma once

#include "OperationOwner.h"
#include "IOutput.h"
#include <assert.h>
#include <math.h>

class MD : public Base::OperationOwner
{
public:
	MD() = default;

private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 2);

		const Data& data = aData[0]->GetOutput();
		const Data& values = aData[1]->GetOutput();
		Number maxDiff = 0.0;

		//Zrobimy to dla jednej osi danych bo mi się nie chce. Jeśli ktoś poda więcej to wywali.
		assert(data.Size() == 2);

		maxDiff = std::abs(data[1][0] - values[1][0]);

		for (int i = 1; i < data[1].Size(); ++i)
		{
			if (std::abs(data[1][i] - values[1][i]) > maxDiff)
			{
				maxDiff = std::abs(data[1][i] - values[1][i]);
			}
		}

		Data result{};
		result.Push(data[0]);
		result.Push(Base::Array{});

		for (int i = 0; i < data[1].Size(); ++i)
		{
			result[1].Push(maxDiff);
		}

		return result;
	}

};