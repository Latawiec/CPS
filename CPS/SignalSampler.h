#pragma once

#include "OperationOwner.h"
#include "IOutput.h"
#include <assert.h>

class SignalSampler : public Base::OperationOwner
{
public:
	SignalSampler(uint32_t aSampleOffset)
	:
	sampleOffset(aSampleOffset)
	{}

private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		assert(aData.size() == 1);

		//Kopiujemy pierwsze dane.
		const Data& data = aData[0]->GetOutput();

		Data result = {};
		result.Push(Base::Array{});
		result.Push(Base::Array{});
		//Dodajemy każdy kolejny do skopiowanego...
		for (uint32_t i = 0; i < data[0].Size(); i+=sampleOffset)
		{
			result[0].Push(data[0][i]);
			result[1].Push(data[1][i]);
		}
		return result;
	}

	uint32_t sampleOffset;
};