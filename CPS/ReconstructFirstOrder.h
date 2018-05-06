#pragma once

#include "Reconstructor.h"
#include "IOutput.h"
#include "Sampler.h"
#include <assert.h>

class ReconstructFirstOrder : public Base::Reconstructor
{
public:
	ReconstructFirstOrder(const Sampler& aSampler)
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
			uint32_t j = 0;
			double diffX, startX, endX;
			double diffY, startY, endY;
			for (uint32_t i = 1; i < data[0].Size(); ++i)
			{
				startX = data[0][i - 1];
				diffX = data[0][i] - data[0][i - 1];

				startY = data[1][i - 1];
				diffY = data[1][i] - data[1][i - 1];

				while (j < result[0].Size() && data[0][i] > result[0][j])
				{
					result[1].Push(startY + diffY*( (double(result[0][j]) - startX)/diffX ));
					++j;
				}
			}
		}
		return result;
	}

};