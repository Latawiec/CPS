#pragma once

#include "OperationOwner.h"
#include <assert.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include "IOutput.h"
#include "Convolution.h"

class Okno {};

class Prostokatne : public Okno
{
public:
	static float Calculate(const uint32_t n, const uint32_t M)
	{
		return 1.0;
	}
};

class Hamming : public Okno
{
public:
	static float Calculate(const uint32_t n, const uint32_t M)
	{
		return 0.53836 - 0.46164*cos((2 * 3.1415926535 * n) / M);
	}
};

class Hanna : public Okno
{
public:
	static float Calculate(const uint32_t n, const uint32_t M)
	{
		return 0.5 - 0.5*cos((2 * 3.1415926535 * n) / M);
	}
};

class Blackman : public Okno
{
public:
	static float Calculate(const uint32_t n, const uint32_t M)
	{
		return 0.42 - 0.5*cos((2 * 3.1415926535 * n) / M) + 0.08*cos((4 * 3.1415926535 * n) / M);
	}
};

enum class FilterType : size_t
{
	Up,
	Middle,
	Down
};

template<class Okno>
class ImpulseResponse : public Base::OperationOwner
{
public:
	ImpulseResponse(const uint32_t n, const uint32_t m, const uint32_t k, FilterType type)
	: N(n)
	, M(m)
	, K(k)
	, type(type)
	{}

private:
	const uint32_t N, M, K;
	const FilterType type;
	float ImpulseResponseCalc(uint32_t n)
	{
		if (n == (M - 1) / 2) {
			return 2.0 / K;
		}
		else {
			double x = 3.1415926535 * (n - (M - 1) / 2);
			return std::sin(2 * x / K) / x;
		}
	}

	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		assert(aData.size() == 0);

		Base::Data impulseResponse;

		impulseResponse.Push({});
		impulseResponse.Push({});

		if (type == FilterType::Up)
		{
			for (uint32_t i = 0; i < N; i++)
			{
				if (i > M)
				{
					double val = ImpulseResponseCalc(i);
					(i % 2) == 0 ? val *= 1 : val *= -1;
					val *= Okno::Calculate(i, M);
					impulseResponse[1].Push(val);
				}
				else
				{
					impulseResponse[1].Push(0.0);
				}
				impulseResponse[0].Push(i);
			}
		}
		else if (type == FilterType::Down)
		{
			for (uint32_t i = 0; i < N; i++)
			{
				if (i < M)
				{
					double val = ImpulseResponseCalc(i);
					(i % 2) == 0 ? val *= 1 : val *= -1;
					val *= Okno::Calculate(i, M);
					impulseResponse[1].Push(val);
				}
				else
				{
					impulseResponse[1].Push(0.0);
				}
				impulseResponse[0].Push(i);
			}
		}
		else
		{
			int fd = 0 + M / 2;
			int fg = N - M / 2;

			for (uint32_t i = 0; i < N; i++)
			{
				if (i >= fd && i <= fg)
				{
					double val = ImpulseResponseCalc(i);
					(i % 2) == 0 ? val *= 1 : val *= -1;
					val *= Okno::Calculate(i, M);
					impulseResponse[1].Push(val);
				}
				else
				{
					impulseResponse[1].Push(0.0);
				}
				impulseResponse[0].Push(i);
			}
		}

		return impulseResponse;
	}
};

template<FilterType Type, class Okno = Prostokatne>
class Filter : public Base::OperationOwner
{
public:
	Filter(const uint32_t n, const uint32_t m, const uint32_t k)
	: impulseResponseOp(n, m, k, Type)
	{}

	const ImpulseResponse<Okno>& GetImpulseResponse()
	{
		return impulseResponseOp;
	}

private:
	Convolution				convolutionOp;
	ImpulseResponse<Okno>	impulseResponseOp;

	Base::Data OperationDefinition(std::vector<const IOutput*> aData) override
	{
		using Base::Data;
		using Numeric::Number;

		assert(aData.size() == 1);
		impulseResponseOp.Execute();

		convolutionOp.AddInput(*aData[0]);
		convolutionOp.AddInput(impulseResponseOp);

		convolutionOp.Execute();

		return convolutionOp.GetOutput();
	}
};