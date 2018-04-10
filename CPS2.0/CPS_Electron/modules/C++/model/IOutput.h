#pragma once

#include "Containers.h"

struct IOutput
{
	virtual ~IOutput() = default;
	virtual const Base::Data& GetOutput() const = 0;
};