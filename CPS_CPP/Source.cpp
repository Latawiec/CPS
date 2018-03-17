#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>
#include "Complex.h"
#include "BasicGenerator.h"
#include "Sum.h"
#include "Multiply.h"
#include "Sinus.h"

#pragma warning(disable:4996)


using namespace std;

template<class T>
void PutToFile(const Base::Output<T>& aOutput)
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << "../QuickDisplay/data/";
	ss << "data_";
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%OH-%OM-%OS");
	ss << ".json";

	fstream file;
	file.open(ss.str(), fstream::out);
	if (file.is_open())
	{
		file << '{' << '\n';
		file << aOutput << endl;
		file << "\"type\": \"scatter\"," << '\n';
		file << "\"name\": \"" << std::put_time(std::localtime(&in_time_t), "%Y - %m - %d_%OS") << "\"\n";
		file << '}';

		file.close();
	}
	else
	{
		throw std::runtime_error("Cannot open file.");
	}
}

int main()
{
	Base::floatComplex a = { 1.0, -1.0 };

	auto generatorIncreasing = BasicGenerator(1.0, 50.0, .1, 8.0);
	generatorIncreasing.Execute();

	auto sum = Sum<double>();
	auto multi = Multiply<double>();
	auto sin = Sin();


	sum.AddInput(generatorIncreasing);
	sum.Execute();

	sin.AddInput(generatorIncreasing);
	sin.Execute();

	multi.AddInput(sin);
	multi.AddInput(sin);
	multi.AddInput(sin);
	multi.AddInput(sum);
	multi.Execute();

	PutToFile(sum);

	return 0;
}