#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>
#include "Complex.h"
#include "Linear.h"
#include "Sum.h"
#include "Subtract.h"
#include "Divide.h"
#include "Multiply.h"
#include "Rand_NormalDistribution.h"
#include "Rand_UniformDistribution.h"
#include "Sinus.h"
#include "SinusFlat.h"
#include "SinusDoubleFlat.h"
#include "Square.h"
#include "Triangle.h"
#include "Step.h"

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

	auto sampler = Base::Sampler(0, 0.01, 1000);

	auto linear = Linear(sampler, 0.0, 1);
	linear.Execute();

	auto minuslinear = Linear(sampler, 0.0, -1);
	minuslinear.Execute();

	auto linearGrowing = Linear(sampler, 3, 1);
	linearGrowing.Execute();

	auto randNormal = RandomNormalDistribution(sampler);
	randNormal.Execute();

	auto randUniform = RandomUniformDistribution(sampler, 5.0);
	randUniform.Execute();
	
	auto sin = Sin(sampler);
	sin.Execute();

	auto sum		= Sum<double>();
	auto multi		= Multiply<double>();
	auto divide		= Divide<double>();
	auto subtract	= Subtract<double>();

	auto sinFlat = SinFlat(sampler);
	sinFlat.Execute();

	auto sinDFlat = SinDoubleFlat(sampler);
	sinDFlat.Execute();

	auto square = Square(sampler, 2.0, 0.2);
	square.Execute();

	auto triangle = Triangle(sampler, 2.0, 0.51);
	triangle.Execute();

	auto step = Step(sampler, 2.0, 3.6);
	step.Execute();

	subtract.AddInput(linear)
			.AddInput(sin)
			.Execute();

	multi.AddInput(randUniform)
		 .AddInput(subtract)
		 .Execute();

	sum.AddInput(multi)
	   .AddInput(linearGrowing)
	   .Execute();

	PutToFile(sum);

	//Teraz tworzenie drzewa operacji bo czemu niby nie?

	sum.ResetInputs()
		.AddInput(multi.ResetInputs()
		               .AddInput(minuslinear)
					   .AddInput(triangle)
					   .Execute())
		.AddInput(sin)
		.Execute();

	PutToFile(sum);
	return 0;
}