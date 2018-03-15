#pragma once

#include <type_traits>
#include <iostream>

namespace Base {

template<typename T>
struct Complex
{
static_assert(std::is_arithmetic<T>::value, "Given type is not arithmetic!");

public:
	Complex() {}

	Complex(const Complex<T>& aComplex)
		: Re(aComplex.Re),
		Im(aComplex.Im)
	{}

	Complex(T aReal)
		: Re(aReal)
	{}

	Complex(T aReal, T aImaginary)
		: Re(aReal),
		Im(aImaginary)
	{}

	/* Asignment operator */
	Complex<T>& operator=(const Complex& aComplex)
	{
		Re = aComplex.Re;
		Im = aComplex.Im;
		return *this;
	}

	/* Comparison */
	bool operator ==(const Complex& aComplex)
	{
		return (Re == aComplex.Re) && (Im == aComplex.Im);
	}

	bool operator !=(const Complex& aComplex)
	{
		return !(*this == aComplex);
	}

	/* Addition */
	Complex<T> operator+(const Complex<T>& aRight)
	{
		return Complex(Re + aRight.Re, Im + aRight.Im);
	}

	Complex<T>& operator+=(const Complex<T>& aRight)
	{
		Re += aRight.Re;
		Im += aRight.Im;
		return *this;
	}

	/* Substraction */
	Complex<T> operator-(const Complex<T>& aRight)
	{
		return Complex(Re - aRight.Re, Im - aRight.Im);
	}

	Complex<T>& operator-=(const Complex<T>& aRight)
	{
		Re -= aRight.Re;
		Im -= aRight.Im;
		return *this;
	}

	/* Multiplication */
	Complex<T> operator*(const Complex<T>& aRight)
	{
		return Complex(Re*aRight.Re - Im*aRight.Im,
			Re*aRight.Im + Im*aRight.Re);
	}

	Complex<T>& operator*=(const Complex<T>& aRight)
	{
		Re = Re*aRight.Re - Im*aRight.Im;
		Im = Re*aRight.Im + Im*aRight.Re;
		return *this;
	}

	/* Division */
	Complex<T> operator/(const Complex<T>& aRight)
	{
		return Complex((Re*aRight.Re + Im*aRight.Im) / (aRight.Re*aRight.Re + aRight.Im*aRight.Im),
			(Im*aRight.Re - Re*aRight.Im) / (aRight.Re*aRight.Re + aRight.Im*aRight.Im));
	}

	Complex<T>& operator/=(const Complex<T>& aRight)
	{
		Re = (Re*aRight.Re + Im*aRight.Im) / (aRight.Re*aRight.Re + aRight.Im*aRight.Im);
		Im = (Im*aRight.Re - Re*aRight.Im) / (aRight.Re*aRight.Re + aRight.Im*aRight.Im);
		return *this;
	}

	T Re = 0;
	T Im = 0;
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Complex<T>& dt)
{
	int a = dt.Re;
	int b = dt.Im;
	os << "( " << dt.Re << ", " << dt.Im << "i )";
	return os;
}

using floatComplex	= Complex<float>;
using doubleComplex = Complex<double>;
using intComplex	= Complex<int>;
}