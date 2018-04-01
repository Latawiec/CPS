#pragma once

#include "Operation.h"
#include <algorithm>

namespace Operation {

struct OperationOwner : public IOperation
{
public:
	IOperation& AddInput(const Base::IOutput& aData) override
	{
		dataSource.push_back(&aData);
		return *this;
	}
	IOperation& RemoveInput(const Base::IOutput& aData) override
	{
		dataSource.erase( std::remove(dataSource.begin(), dataSource.end(), &aData), dataSource.end() );
		return *this;
	}

	IOperation& Execute() override
	{
		output = OperationDefinition(dataSource);
		return *this;
	}

	const Base::Data& GetOutput() const override
	{
		return output;

	}

	virtual Base::Data OperationDefinition(std::vector<const Base::IOutput*> aData) = 0;

private:
	std::vector<const Base::IOutput*> dataSource;
	Base::Data						  output;
};

} /* namespace Operation */