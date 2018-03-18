#pragma once


#include "Containers.h"
#include "IOutput.h"

namespace Base {

struct IOperation : public IOutput
{
	virtual ~IOperation() = default;

	virtual IOperation& AddInput(const IOutput& aData) = 0;
	virtual IOperation& RemoveInput(const IOutput& aData) = 0;

	virtual IOperation& Execute() = 0;
};
}