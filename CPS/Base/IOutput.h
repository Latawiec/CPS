#pragma once

#include "Containers.h"

namespace Base {

struct IOutput
{
	virtual ~IOutput() = default;
	virtual const Data& GetOutput() const = 0;
};

} /* namespace Base */