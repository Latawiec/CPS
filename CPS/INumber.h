#pragma once

namespace Numeric {

struct INumber
{
	enum class Type : uint8_t
	{
		Unknown = 0,
		Real = 1,
		Complex = 2
	};

	virtual ~INumber() = default;

	virtual INumber* clone() const = 0;

	virtual INumber* Add(const INumber* rValue) const = 0;
	virtual INumber& AddHere(const INumber* rValue) = 0;

	virtual INumber* Subtract(const INumber* rValue) const = 0;
	virtual INumber& SubtractHere(const INumber* rValue) = 0;

	virtual INumber* Multiply(const INumber* rValue) const = 0;
	virtual INumber& MultiplyHere(const INumber* rValue) = 0;

	virtual INumber* Divide(const INumber* rValue) const = 0;
	virtual INumber& DivideHere(const INumber* rValue) = 0;

	virtual bool Compare(const INumber* rValue) const = 0;

	virtual Type GetType() const = 0;

	virtual const double* GetValues() const = 0;
	};

}