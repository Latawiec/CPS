#pragma once

#include "OperationOwner.h"
#include "IOutput.h"
#include <assert.h>

class Multiply : public Base::OperationOwner
{
public:
	Multiply() = default;

private:
	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		assert(aData.size() > 0);

		//Kopiujemy pierwsze dane.
		Data result = aData[0]->GetOutput();

		//Dodajemy każdy kolejny do skopiowanego...
		for (int i = 1; i < aData.size(); ++i)
		{
			//I nie sumujemy pierwszych wektorów. To są nasze argumenty jakby.
			for (int j = 1; j < aData[i]->GetOutput().Size(); ++j)
			{
				for (int k = 0; k < aData[i]->GetOutput()[j].Size(); ++k)
				{
					result[j][k] *= aData[i]->GetOutput()[j][k];
				}
			}
		}
		return result;
	}

};