#pragma once

#include <vector>

namespace Base {

template<class T>
struct Input
{
	Input<T>& AddInput(const Output<T>& aInput)
	{
		inputs.push_back(&aInput);
		return *this;
	}

protected:
	std::vector<const Output<T>*> inputs;
};

}