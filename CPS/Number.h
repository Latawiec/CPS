#pragma once

#include <memory>

#include "INumber.h"
#include "Complex.h"
#include "Real.h"

namespace Numeric {

class Number
{
public:

	Number(double Re)
		: numberPimpl(new RealNumber(Re))
	{}

	Number(double Re, double Im)
		: numberPimpl(new ComplexNumber(Re, Im))
	{}

	Number(const Number& aNumber)
	{
		numberPimpl.reset(aNumber.numberPimpl->clone());
	}

	operator double() const
	{
		return numberPimpl->GetValues()[0];
	}

	Number& operator=(const Number& aNumber)
	{
		numberPimpl.reset(aNumber.numberPimpl->clone());
		return *this;
	}

	Number operator+(const Number& aNumber) const
	{
		return Number(numberPimpl->Add(aNumber.numberPimpl.get()));
	}
	Number& operator+=(const Number& aNumber)
	{
		numberPimpl->AddHere(aNumber.numberPimpl.get());
		return *this;
	}

	Number operator-(const Number& aNumber) const
	{
		return Number(numberPimpl->Subtract(aNumber.numberPimpl.get()));
	}
	Number& operator-=(const Number& aNumber)
	{
		numberPimpl->SubtractHere(aNumber.numberPimpl.get());
		return *this;
	}

	Number operator*(double aValue) const
	{
		return Number(numberPimpl->Multiply(aValue));
	}
	Number operator*(const Number& aNumber) const
	{
		return Number(numberPimpl->Multiply(aNumber.numberPimpl.get()));
	}
	Number& operator*=(double aValue)
	{
		numberPimpl->MultiplyHere(aValue);
		return *this;
	}
	Number& operator*=(const Number& aNumber)
	{
		numberPimpl->MultiplyHere(aNumber.numberPimpl.get());
		return *this;
	}

	
	Number operator/(double aValue) const
	{
		return Number(numberPimpl->Divide(aValue));
	}
	Number operator/(const Number& aNumber) const
	{
		return Number(numberPimpl->Divide(aNumber.numberPimpl.get()));
	}
	Number& operator/=(double aValue)
	{
		numberPimpl->DivideHere(aValue);
		return *this;
	}
	Number& operator/=(const Number& aNumber)
	{
		numberPimpl->DivideHere(aNumber.numberPimpl.get());
		return *this;
	}

	INumber::Type Type() const
	{
		return numberPimpl->GetType();
	}

private:
	Number(INumber* impl)
		:
		numberPimpl(impl)
	{}

	std::unique_ptr<INumber> numberPimpl;
};

}