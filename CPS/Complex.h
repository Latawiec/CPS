#pragma once

#include "INumber.h"

namespace Numeric {

struct ComplexNumber : public INumber
{
	ComplexNumber(double aRe, double aIm)
		: Re(aRe)
		, Im(aIm)
	{}

	~ComplexNumber() {}

	INumber* clone() const override
	{
		return new ComplexNumber(Re, Im);
	}

	INumber* Add(const INumber* rValue) const override
	{
		return new ComplexNumber(Re + rValue->GetValues()[0],
			Im + rValue->GetValues()[1]);
	}
	INumber& AddHere(const INumber* rValue) override
	{
		Re += rValue->GetValues()[0];
		Im += rValue->GetValues()[1];
		return *this;
	}

	INumber* Subtract(const INumber* rValue) const override
	{
		return new ComplexNumber(Re - rValue->GetValues()[0],
			Im - rValue->GetValues()[1]);
	}
	INumber& SubtractHere(const INumber* rValue) override
	{
		Re -= rValue->GetValues()[0];
		Im -= rValue->GetValues()[1];
		return *this;
	}

	INumber* Multiply(const INumber* rValue) const override
	{
		return new ComplexNumber(Re * rValue->GetValues()[0] - Im * rValue->GetValues()[1],
			Re * rValue->GetValues()[1] + Im * rValue->GetValues()[0]);
	}
	INumber& MultiplyHere(const INumber* rValue) override
	{
		Re = Re * rValue->GetValues()[0] - Im * rValue->GetValues()[1];
		Im = Re * rValue->GetValues()[1] + Im * rValue->GetValues()[0];
		return *this;
	}

	INumber* Divide(const INumber* rValue) const override
	{
		return new ComplexNumber((Re*rValue->GetValues()[0] + Im*rValue->GetValues()[1]) / (rValue->GetValues()[0] * rValue->GetValues()[0] + rValue->GetValues()[1] * rValue->GetValues()[1]),
			(Im*rValue->GetValues()[0] - Re*rValue->GetValues()[1]) / (rValue->GetValues()[0] * rValue->GetValues()[0] + rValue->GetValues()[1] * rValue->GetValues()[1]));
	}
	INumber& DivideHere(const INumber* rValue) override
	{
		Re = (Re*rValue->GetValues()[0] + Im*rValue->GetValues()[1]) / (rValue->GetValues()[0] * rValue->GetValues()[0] + rValue->GetValues()[1] * rValue->GetValues()[1]);
		Im = (Im*rValue->GetValues()[0] - Re*rValue->GetValues()[1]) / (rValue->GetValues()[0] * rValue->GetValues()[0] + rValue->GetValues()[1] * rValue->GetValues()[1]);
		return *this;
	}

	bool Compare(const INumber* rValue) const override
	{
		return Re == rValue->GetValues()[0] &&
			Im == rValue->GetValues()[1];
	}

	Type GetType() const override
	{
		return Type::Complex;
	}

	const double* GetValues() const override
	{
		return values;
	}


private:
	union {
		double values[2];
		struct {
			double Re;
			double Im;
		};
	};
};

}