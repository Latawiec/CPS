#pragma once

#include <iostream>

namespace Base {

class Serializable
{
public:

	virtual ~Serializable() = default;

	virtual void Serialize(std::ostream& aStream) const
	{
		aStream << "No specific serialization defined.";
	}
};

std::ostream& operator<<(std::ostream& aStream, const Serializable& aSerializable)
{
	aSerializable.Serialize(aStream);
	return aStream;
}

} /* namespace Base */