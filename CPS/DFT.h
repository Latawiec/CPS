﻿#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include "IOutput.h"

class DFT : public Base::OperationOwner
{
public:
	DFT() = default;

	static Numeric::Number ei(const double x)
	{
		return Numeric::Number(std::cos(x), -std::sin(x));
	}

private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		double two_PI = 6.283185307179586;
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 1);

		const Data& data = aData[0]->GetOutput();
		assert(data.Size() == 2);

		uint32_t dataSize = data[1].Size();
		Base::Array dftValues(dataSize);

		for (uint32_t m = 0; m < dataSize; ++m)
		{
			Number result(0, 0);
			uint32_t n = 0;
			for (const auto& value : data[1])
			{
				// Robimy z tego "value" liczbe zespolona.
				result += Number(value, 0) * ei( (two_PI * double(m) * double(n)) / double(dataSize) );
				n++;
			}
			dftValues.Push(std::move(result));
		}

		Data result{};
		result.Push(data[0]);
		result.Push(std::move(dftValues));

		return result;
	}

};