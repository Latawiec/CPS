#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include "IOutput.h"

class FDCTII : public Base::OperationOwner
{
public:
	FDCTII() = default;

	static double c(uint32_t m, const double N)
	{
		return m == 0 ? std::sqrt(1.0 / N) : std::sqrt(2.0 / N);
	}

	static Numeric::Number ei(const double x)
	{
		return Numeric::Number(std::cos(x), -std::sin(x));
	}

	static Base::Array DFT(const Base::Array& values)
	{
		double two_PI = 6.283185307179586;
		using Base::Data;
		using Numeric::Number;

		uint32_t dataSize = values.Size();
		Base::Array dftValues(dataSize);

		for (uint32_t m = 0; m < dataSize; ++m)
		{
			Number result(0, 0);
			uint32_t n = 0;
			for (const auto& value : values)
			{
				// Robimy z tego "value" liczbe zespolona.
				result += Number(value, 0) * ei((two_PI * double(m) * double(n)) / double(dataSize));
				n++;
			}
			dftValues.Push(std::move(result));
		}

		return dftValues;
	}

private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		double PI = 3.1415926535;
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 1);

		const Data& data = aData[0]->GetOutput();
		assert(data.Size() == 2);

		uint32_t dataSize = data[1].Size();
		Base::Array dftValues(dataSize);

		for (uint32_t i = 0; i < dataSize; i+=2)
		{
			dftValues.Push(Number(data[1][i],0));
		}
		{
			uint8_t isOdd = dataSize % 2 ? 0 : 1;
			for (int i = dataSize - isOdd; i >= 1; i-=2)
			{
				dftValues.Push(Number(data[1][i], 0));
			}
		}

		dftValues = DFT(dftValues);

		double PiByN = PI / dataSize;

		for (uint32_t m = 0; m < dataSize; ++m)
		{
			dftValues[m] = Number((ei((PI*m) / (2.0*dataSize)) * c(m, dataSize) * dftValues[m]).Re());
		}

		Data result{};
		result.Push(data[0]);
		result.Push(std::move(dftValues));

		return result;
	}

};