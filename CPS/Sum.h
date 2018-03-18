#pragma once

#include "OperationOwner.h"
#include <assert.h>

class Sum : public Base::OperationOwner
{
public:
	Sum() = default;

private:
	Base::Data OperationDefinition(std::vector<const Base::Data*> aData) override
	{
		using Base::Data;
		assert(aData.size() > 0);

		//Kopiujemy pierwsze dane.
		Data result = *aData[0];
		
		//Dodajemy każdy kolejny do skopiowanego...
		for (int i = 1; i < aData.size(); ++i)
		{
			//I nie sumujemy pierwszych wektorów. To są nasze argumenty jakby.
			for (int j = 1; j < aData[i]->Size(); ++j)
			{
				for (int k = 0; k < (*aData[i])[j].Size(); ++k)
				{
					result[j][k] += (*aData[i])[j][k];
				}
			}
		}
		return result;
	}

};