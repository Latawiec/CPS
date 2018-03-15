#pragma once

#include "Operation.h"
#include "Output.h"

template<class T>
struct Sum : public Base::Operation<T>
{
	Base::Output<T> OperationDefinition(const std::vector<const Base::Output<T>*>& aInputData)
	{
		std::vector<double> x;
		std::vector<T>		y;

		//Pierwsze dane możemy skopiować.
		x = aInputData[0]->GetX();
		y = aInputData[0]->GetY();

		for (size_t i = 1; i < aInputData.size(); ++i)
		{
			for (size_t j = 0; j < aInputData[i]->GetY().size(); ++j)
			{
				y[j] += aInputData[i]->GetY()[j];
			}
		}

		return Base::Output<T>(x, y);
	}
};