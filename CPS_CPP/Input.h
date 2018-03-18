#pragma once

#include <vector>

namespace Base {

template<class T>
struct Input
{
protected:
	Input<T>& AddInput(const Output<T>& aInput)
	{
		inputs.push_back(&aInput);
		return *this;
	}

	void ClearInputs()
	{
		inputs.clear();
	}
	std::vector<const Output<T>*> inputs;
};

}