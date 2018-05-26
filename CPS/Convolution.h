#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include <algorithm>
#include "IOutput.h"

class Convolution : public Base::OperationOwner
{
public:
	Convolution() = default;

private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		using Numeric::Number;

		// Musimy mieć choć dwa zestawy.
		assert(aData.size() == 2);

		// Pierwszy jest inny, bo tworzymy dopiero co sobie jakiś output.
		Data lastResult = {};
		
		const Data& one = aData[0]->GetOutput();
		const Data& two = aData[1]->GetOutput();

		uint32_t outputSize = one[1].Size() + two[1].Size() - 1;

		lastResult.Push(Base::Array(outputSize));
		for (uint32_t i = 0; i < outputSize; ++i) {
			lastResult[0].Push(i);
		}
		lastResult.Push({});

		for (uint32_t i = 0; i < outputSize; ++i)
		{
			{
				int32_t j = i;
				Number val{ 0.0 };
				while (j>=0)
				{
					if( j < one[1].Size()  && (i-j) < two[1].Size() )
					{
						val += one[1][j] * two[1][i - j];
					}
					--j;
					continue;
				}

				lastResult[1].Push(val);
			}
		}
		return lastResult;
	}
};