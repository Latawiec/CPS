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
	INumber* Multiply(double aValue) const override
	{
		return new RealNumber(Value * aValue);
	}
	INumber& MultiplyHere(const INumber* rValue) override
	{
		Value *= rValue->GetValues()[0];
		return *this;
	}
	INumber& MultiplyHere(double aValue) override
	{
		Value *= aValue;
		return *this;
	}

	INumber* Divide(const INumber* rValue) const override
	{
		return new RealNumber(Value / rValue->GetValues()[0]);
	}
	INumber* Divide(double aValue) const override
	{
		return new RealNumber(Value / aValue);
	}
	INumber& DivideHere(const INumber* rValue) override
	{
		Value /= rValue->GetValues()[0];
		return *this;
	}
	INumber& DivideHere(double aValue) override
	{
		Value /= aValue;
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

	virtual INumber* Mod() const override
	{
		return new RealNumber(std::sqrt(Value*Value));
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