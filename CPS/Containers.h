#pragma once

#include <vector>
#include <string>
#include "Number.h"
#include "Serializable.h"

#pragma warning(disable:4996)

namespace Base
{

struct Array
{
	Array() = default;
	Array(int aSize)
	{
		values.reserve(aSize);
	}
	Array(int aSize, Numeric::Number aValue)
	{
		values = std::vector<Numeric::Number>(aSize, aValue);
	}
	Array(const Array& aArray)
	: values(aArray.values.begin(), aArray.values.end())
	{}

	Array(Array&& aArray)
	: values(std::move(aArray.values))
	{}

	Array& operator=(const Array& aArray)
	{
		values = std::vector<Numeric::Number>(aArray.values.begin(), aArray.values.end());
		return *this;
	}

	void Push(Numeric::Number aNumber)
	{
		values.push_back(std::move(aNumber));
	}

	void Clear()
	{
		values.clear();
	}

	Numeric::Number& operator[](unsigned int aIndex)
	{
		return values[aIndex];
	}

	const Numeric::Number& operator[](unsigned int aIndex) const
	{
		return values[aIndex];
	}

	const std::vector<Numeric::Number>& GetRaw() const
	{
		return values;
	}

	size_t Size() const
	{
		return values.size();
	}

	Numeric::INumber::Type Type() const
	{
		if (values.size() == 0)
		{
			return Numeric::INumber::Type::Unknown;
		}
		else
		{
			return values[0].Type();
		}
	}

protected:
	std::vector<Numeric::Number> values;
};

struct Data : public Serializable
{
	Data() = default;
	Data(int aSize)
	{
		arrays.reserve(aSize);
	}
	Data(const Data& aData)
		: arrays(aData.arrays.begin(), aData.arrays.end())
	{}

	Data& operator=(const Data& aData)
	{
		this->arrays = std::vector<Array>(aData.arrays.begin(), aData.arrays.end());
		return *this;
	}

	Data(Data&& aData)
		: arrays(std::move(aData.arrays))
	{}

	void Push(Array aArray)
	{
		arrays.push_back(std::move(aArray));
	}

	Array& operator[](unsigned int aIndex)
	{
		return arrays[aIndex];
	}

	const Array& operator[](unsigned int aIndex) const
	{
		return arrays[aIndex];
	}

	size_t Size() const
	{
		return arrays.size();
	}

	void Clear()
	{
		arrays.clear();
	}

	void Serialize(std::ostream& aStream) const override
	{
		char dumbAxisName = 'x';
		for (const auto& array : arrays)
		{
			aStream << '\t' << '\"' << dumbAxisName << '\"' << ": [";
			aStream << double(array[0]);
			for (unsigned int i = 1; i < array.Size(); ++i)
			{
				aStream << ',' << double(array[i]);
			}
			aStream << "],\n";

			if (array.Type() == Numeric::INumber::Type::Complex)
			{
				aStream << "//Cannot serialize Complex numbers yet :(((\n";
				//Add serialization of imaginary part. There's no function provided for fetching that value yet xD.
			}
			dumbAxisName++;
		}
	}

protected:
	std::vector<Array> arrays;
};
}
