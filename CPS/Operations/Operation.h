#pragma once


#include "Containers.h"
#include "IOutput.h"

namespace Operation {

struct IOperation : public Base::IOutput
{
	virtual ~IOperation() = default;

	virtual IOperation& AddInput(const Base::IOutput& aData) = 0;
	virtual IOperation& RemoveInput(const Base::IOutput& aData) = 0;

	virtual IOperation& Execute() = 0;
};

} /* namespace Operation */