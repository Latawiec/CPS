#pragma once

#include "Operation.h"
#include <algorithm>

namespace Base{

struct OperationOwner : public IOperation
{
public:
	IOperation& AddInput(const Data& aData) override
	{
		dataSource.push_back(&aData);
		return *this;
	}
	IOperation& RemoveInput(const Data& aData) override
	{
		dataSource.erase( std::remove(dataSource.begin(), dataSource.end(), &aData), dataSource.end() );
		return *this;
	}

	IOperation& Execute() override
	{
		output = OperationDefinition(dataSource);
		return *this;
	}

	const Data& GetOutput() const override
	{
		return output;
	}

	virtual Data OperationDefinition(std::vector<const Data*> aData) = 0;

private:
	std::vector<const Data*> dataSource;
	Data					 output;
};

}