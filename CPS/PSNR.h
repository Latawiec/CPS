#pragma once

#include "OperationOwner.h"
#include "IOutput.h"
#include <assert.h>
#include <math.h>

class PSNR : public Base::OperationOwner
{
public:
	PSNR() = default;

private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 2);

		const Data& data = aData[0]->GetOutput();
		const Data& values = aData[1]->GetOutput();
		double mseValue = 0.0;
		double psnr = 0.0;

		//Zrobimy to dla jednej osi danych bo mi się nie chce. Jeśli ktoś poda więcej to wywali.
		assert(data.Size() == 2);

		for (int i = 0; i < data[1].Size(); ++i)
		{
			double temp = data[1][i] - values[1][i];
			mseValue += temp*temp;
		}

		mseValue /= data[1].Size();

		double maxValue = data[1][0];
		for (int i = 0; i < data[1].Size(); ++i)
		{
			if (data[1][i] > maxValue)
			{
				maxValue = data[1][i];
			}
		}

		psnr = 10.0 * std::log10(maxValue / mseValue);

		Data result{};
		result.Push(data[0]);
		result.Push(Base::Array{});

		for (int i = 0; i < data[1].Size(); ++i)
		{
			result[1].Push(psnr);
		}

		return result;
	}

};