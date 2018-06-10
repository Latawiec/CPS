#pragma once

#include "INumber.h"
#include "Real.h"

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

	INumber* Multiply(double rValue) const override
	{
		return new ComplexNumber(Re * rValue,
								 Im * rValue);
	}
	INumber* Multiply(const INumber* rValue) const override
	{
		return new ComplexNumber(Re * rValue->GetValues()[0] - Im * rValue->GetValues()[1],
								 Re * rValue->GetValues()[1] + Im * rValue->GetValues()[0]);
	}
	INumber& MultiplyHere(const INumber* rValue) override
	{
		const double currentRe = Re;
		Re = currentRe * rValue->GetValues()[0] - Im * rValue->GetValues()[1];
		Im = currentRe * rValue->GetValues()[1] + Im * rValue->GetValues()[0];
		return *this;
	}
	INumber& MultiplyHere(double aValue) override
	{
		Re = Re * aValue;
		Im = Im * aValue;
		return *this;
	}

	INumber* Divide(const INumber* rValue) const override
	{
		return new ComplexNumber((Re*rValue->GetValues()[0] + Im*rValue->GetValues()[1]) / (rValue->GetValues()[0] * rValue->GetValues()[0] + rValue->GetValues()[1] * rValue->GetValues()[1]),
								 (Im*rValue->GetValues()[0] - Re*rValue->GetValues()[1]) / (rValue->GetValues()[0] * rValue->GetValues()[0] + rValue->GetValues()[1] * rValue->GetValues()[1]));
	}
	INumber* Divide(double aValue) const override
	{
		return new ComplexNumber(Re / aValue,
							     Im / aValue);
	}
	INumber& DivideHere(const INumber* rValue) override
	{
		const double currentRe = Re;
		Re = (currentRe*rValue->GetValues()[0] + Im*rValue->GetValues()[1])		   / (rValue->GetValues()[0] * rValue->GetValues()[0] + rValue->GetValues()[1] * rValue->GetValues()[1]);
		Im = (Im*rValue->GetValues()[0]		   - currentRe*rValue->GetValues()[1]) / (rValue->GetValues()[0] * rValue->GetValues()[0] + rValue->GetValues()[1] * rValue->GetValues()[1]);
		return *this;
	}
	INumber& DivideHere(double aValue) override
	{
		Re = Re / aValue;
		Im = Im / aValue;
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

	virtual INumber* Mod() const override
	{
		return new RealNumber(std::sqrt(Re*Re + Im*Im));
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