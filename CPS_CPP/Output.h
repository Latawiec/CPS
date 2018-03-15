#pragma once

#include <vector>

namespace Base {

template<class T>
struct Output
{
	Output(std::vector<double> x, std::vector<T> y)
		:
		X(std::move(x)),
		Y(std::move(y))
	{}

	Output() = default;

	void PushValue(double x, T y)
	{
		X.push_back(std::move(x));
		Y.push_back(std::move(y));
	}

	const std::vector<T>& GetX() const
	{
		return X;
	}

	virtual const std::vector<double>& GetY() const
	{
		return Y;
	}

protected:
	std::vector<double> X;
	std::vector<T>		Y;
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Output<T>& dt)
{
	//X
	os << "x: [";
	os << dt.GetX()[0];
	for (size_t i = 0; i < dt.GetX().size(); ++i)
	{
		os << ',' << dt.GetX()[i];
	}
	os << "],\n";

	//Y
	os << "y: [";
	os << dt.GetY()[0];
	for (size_t i = 0; i < dt.GetY().size(); ++i)
	{
		os << ',' << dt.GetY()[i];
	}
	os << "],\n";

	return os;
}

}