#pragma once

#include "INumber.h"

namespace Numeric {

struct RealNumber : public INumber
{
	RealNumber(double aValue)
		: Value(aValue)
		, Dummy(0)
	{}

	~RealNumber() {}

	INumber* clone() const override
	{
		return new RealNumber(Value);
	}

	INumber* Add(const INumber* rValue) const override
	{
		return new RealNumber(Value + rValue->GetValues()[0]);
	}
	INumber& AddHere(const INumber* rValue) override
	{
		Value += rValue->GetValues()[0];
		return *this;
	}

	INumber* Subtract(const INumber* rValue) const override
	{
		return new RealNumber(Value - rValue->GetValues()[0]);
	}
	INumber& SubtractHere(const INumber* rValue) override
	{
		Value -= rValue->GetValues()[0];
		return *this;
	}

	INumber* Multiply(const INumber* rValue) const override
	{
		return new RealNumber(Value * rValue->GetValues()[0]);
	}
	INumber& MultiplyHere(const INumber* rValue) override
	{
		Value *= rValue->GetValues()[0];
		return *this;
	}

	INumber* Divide(const INumber* rValue) const override
	{
		return new RealNumber(Value / rValue->GetValues()[0]);
	}
	INumber& DivideHere(const INumber* rValue) override
	{
		Value /= rValue->GetValues()[0];
		return *this;
	}

	bool Compare(const INumber* rValue) const override
	{
		return Value == rValue->GetValues()[0];
	}

	Type GetType() const override
	{
		return Type::Real;
	}

	const double* GetValues() const override
	{
		return &Value;
	}

private:
	union {
		double values[2];
		struct {
			double Value;
			const double Dummy;
		};
	};
};

}