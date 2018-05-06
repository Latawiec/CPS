#pragma once

#include "Reconstructor.h"
#include "IOutput.h"
#include "Sampler.h"
#include <assert.h>

class ReconstructZeroOrder : public Base::Reconstructor
{
public:
	ReconstructZeroOrder(const Sampler& aSampler)
	: Reconstructor(aSampler)
	{}

private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 1);

		const Data& data = aData[0]->GetOutput();
		
		//Zrobimy to dla jednej osi danych bo mi się nie chce. Jeśli ktoś poda więcej to wywali.
		assert(data.Size() == 2);

		Data result{};
		result.Push(samplerData);
		result.Push({});
		{
			uint32_t j = 1;
			result[1].Push(data[1][0]);
			for (uint32_t i = 0; i < data[0].Size(); ++i)
			{
				while (j < result[0].Size() && data[0][i] > result[0][j])
				{
					result[1].Push(data[1][i-1]);
					++j;
				}
			}
		}
		return result;
	}

};