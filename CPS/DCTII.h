#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include "IOutput.h"

class DCTII : public Base::OperationOwner
{
public:
	DCTII() = default;

	static double c(uint32_t m, const double N)
	{
		return m == 0 ? std::sqrt(1.0 / N) : std::sqrt(2.0 / N);
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
		Base::Array dctValues(dataSize);
		double PiByN = PI / dataSize;
		for (uint32_t m = 0; m < dataSize; ++m)
		{
			Number result(0.0);
			uint32_t n = 0;
			for (const auto& value : data[1])
			{
				result += value * std::cos(PiByN * (double(n) + 0.5) * double(m) );
				n++;
			}
			result *= c(m, dataSize);
			dctValues.Push(std::move(result));
		}

		Data result{};
		result.Push(data[0]);
		result.Push(std::move(dctValues));

		return result;
	}

};