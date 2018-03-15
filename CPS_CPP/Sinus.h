#pragma once

#include "Operation.h"
#include "Output.h"
#include "assert.h"
#include <math.h>

struct Sin : public Base::Operation<double>
{
	Base::Output<double> OperationDefinition(const std::vector<const Base::Output<double>*>& aInputData)
	{
		//Tylko jednego argumentu oczekujemy.
		assert(1 == aInputData.size());

		std::vector<double> x;
		std::vector<double>	y;

		x = aInputData[0]->GetX();
		y.reserve(x.size());

		for (const auto& value : x)
		{
			y.push_back(std::sin(value));
		}

		return Base::Output<double>(x, y);
	}
};