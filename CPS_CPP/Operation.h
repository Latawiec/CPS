#pragma once

#include "Output.h"
#include "Input.h"

namespace Base {

template<class In, class Out = In>
struct Operation : public Input<In>, public Output<Out>
{
	virtual ~Operation() = default;

	Operation& Execute()
	{
		static_cast<Output<Out>&>(*this) = OperationDefinition(this->inputs);
		return *this;
	}

	Operation& AddInput(const Output<In>& aInput)
	{
		this->Input<In>::AddInput(aInput);
		return *this;
	}

	Operation& ResetInputs()
	{
		ClearInputs();
		return *this;
	}

	virtual Output<Out> OperationDefinition(const std::vector<const Output<In>*>& aInputData) = 0;
};
}