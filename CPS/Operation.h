#pragma once


#include "Containers.h"

namespace Base {

struct IOperation
{
	virtual ~IOperation() = default;

	virtual IOperation& AddInput(const Data& aData) = 0;
	virtual IOperation& RemoveInput(const Data& aData) = 0;

	virtual IOperation& Execute() = 0;
	virtual const Data& GetOutput() const = 0;
};
}