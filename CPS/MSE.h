#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include "IOutput.h"

class MSE : public Base::OperationOwner
{
public:
	MSE() = default;

private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 2);

		const Data& data = aData[0]->GetOutput();
		const Data& values = aData[1]->GetOutput();
		double mseValue = 0.0;

		//Zrobimy to dla jednej osi danych bo mi się nie chce. Jeśli ktoś poda więcej to wywali.
		assert(data.Size() == 2);

		for (int i = 0; i < data[1].Size(); ++i)
		{
			double temp = data[1][i] - values[1][i];
			mseValue += temp*temp;
		}

		mseValue /= data[1].Size();

		Data result{};
		result.Push(data[0]);
		result.Push(Base::Array{});

		for (int i = 0; i < data[1].Size(); ++i)
		{
			result[1].Push(mseValue);
		}

		return result;
	}

};