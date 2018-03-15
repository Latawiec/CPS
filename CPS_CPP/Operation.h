#pragma once

#include "Output.h"
#include "Input.h"

namespace Base {

template<class In, class Out = In>
struct Operation : public Input<In>, public Output<Out>
{
	virtual ~Operation() = default;

	void Execute()
	{
		static_cast<Output<Out>&>(*this) = OperationDefinition(this->inputs);
	}

	virtual Output<Out> OperationDefinition(const std::vector<const Output<In>*>& aInputData) = 0;
};
}