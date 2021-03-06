#pragma once

#include "Operation.h"
#include "Sampler.h"
#include <algorithm>

namespace Base {

	struct Reconstructor : public IOperation, public IOutput
	{
	public:

		Reconstructor(const Sampler& aSampler)
		: samplerData(aSampler.Get())
		{}

		IOperation& AddInput(const IOutput& aData) override
		{
			dataSource.push_back(&aData);
			return *this;
		}
		IOperation& RemoveInput(const IOutput& aData) override
		{
			dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), &aData), dataSource.end());
			return *this;
		}

		IOperation& Execute() override
		{
			output = OperationDefinition(dataSource);
			return *this;
		}

		const Data& GetOutput() const override
		{
			return output;
		}

		virtual Data OperationDefinition(std::vector<const IOutput*> aData) = 0;

	protected:
		const Array&					samplerData;

	private:
		std::vector<const IOutput*> dataSource;
		Data						output;
	};
}