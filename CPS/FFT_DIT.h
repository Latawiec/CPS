#pragma once

#include "OperationOwner.h"
#include "Number.h"
#include <assert.h>
#include <bitset>
#include <map>
#include "IOutput.h"

class FFT_DIT : public Base::OperationOwner
{
public:
	FFT_DIT() = default;

	static Numeric::Number ei(const double x)
	{
		return Numeric::Number(std::cos(x), -std::sin(x));
	}



private:
	class TwiddleFactors
	{
	public:
		TwiddleFactors(uint32_t N)
		: N(N)
		{
			double two_PI = 6.2831853071795864;;
			_values.reserve(N);
			for(uint32_t i = 0; i < N; ++i)
			{
				_values.push_back(ei((two_PI * double(i)) / double(N)));
			}
		}

		const Numeric::Number& Get(uint32_t k)
		{
			return _values[k];
		}
	private:
		std::vector<Numeric::Number> _values;
		const uint32_t N;
	};

	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		double two_PI = 6.2831853071795864;
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 1);

		const Data& data = aData[0]->GetOutput();
		Number averageValue = 0.0;

		//Zrobimy to dla jednej osi danych bo mi się nie chce. Jeśli ktoś poda więcej to wywali.
		assert(data.Size() == 2);

		uint32_t dataSize = data[1].Size();
		// Musi być to potęga 2.
		assert(std::bitset<sizeof(decltype(dataSize)) * 8>(dataSize).count() == 1);
		uint32_t numberOfStages = [=]()mutable->uint32_t {
			uint32_t num = 0;
			while (dataSize = dataSize >> 1) {
				++num;
			}
			return num;
		}();

		// Taktyczna kopia
		Base::Array fftValues(data[1].Size());
		for (const auto& value : data[1])
		{
			fftValues.Push(Number(value, 0));
		}

		// Taktyczna zamiana kolejności aby była adekwatna do FFT
		for (uint32_t i = 0; i < fftValues.Size() / 2; ++i)
		{
			uint32_t original = i;
			uint32_t flipped = 0;
			for (uint8_t b = 0; b < numberOfStages; ++b)
			{
				flipped = flipped << 1;
				flipped |= (original & 0x1);
				original = original >> 1;
			}
			std::swap(fftValues[i], fftValues[flipped]);
		}

		// Właście FFT
		for (uint32_t stage = 0; stage < numberOfStages; ++stage)
		{
			uint32_t samplesInGroup = 1 << (stage+1);
			uint32_t groupsInStage = fftValues.Size() / samplesInGroup;

			TwiddleFactors twFactors(samplesInGroup);

			for (uint32_t group = 0; group < groupsInStage; ++group)
			{
				for (uint32_t sample = 0; sample < samplesInGroup / 2; ++sample)
				{
					uint32_t sampleIndex = samplesInGroup * group + sample;

					fftValues[sampleIndex + samplesInGroup/2] *= twFactors.Get(sample);
					Number tempFirst = fftValues[sampleIndex];

					fftValues[sampleIndex]					  = tempFirst + fftValues[sampleIndex + samplesInGroup/2];
					fftValues[sampleIndex + samplesInGroup/2] = tempFirst - fftValues[sampleIndex + samplesInGroup/2];
				}
			}
		}

		Data result{};
		result.Push(data[0]);
		result.Push(std::move(fftValues));

		return result;
	}

};