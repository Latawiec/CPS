#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "Complex.h"
#include "Number.h"

#include "Sum.h"
#include "Divide.h"
#include "Multiply.h"
#include "Subtract.h"

#include "Sampler.h"

#include "Linear.h"
#include "Sinus.h"
#include "SinusFlat.h"
#include "SinusPositive.h"
#include "Square.h"
#include "Triangle.h"
#include "Step.h"
#include "RandNormal.h"
#include "RandUniform.h"

using namespace std;
using namespace Numeric;

void PutToFile(const Base::Data& aOutput)
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::random_device generator{};
	std::uniform_int_distribution<int> distribution(-10000, 10000);
	int value = distribution(generator);

	std::stringstream ss;
	ss << "../QuickDisplay/data/";
	ss << "data_";
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%OH-%OM-%OS");
	ss << "_" << value;
	ss << ".json";

	fstream file;
	file.open(ss.str(), fstream::out);
	if (file.is_open())
	{
		file << '{' << '\n';
		file << aOutput << endl;
		file << "\"type\": \"scatter\"," << '\n';
		file << "\"name\": \"" << std::put_time(std::localtime(&in_time_t), "%Y - %m - %d_%OS") << "\"\n";
		ss << "_" << value;
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
	Sum				sumOP{};
	Sum				sumOP1{};
	Divide			divOP{};
	Multiply		mulOP{};
	Multiply		mulOP1{};
	Subtract		subOP{};

	Sampler a(0, 0.01, 9);

	Sin				sinOp(a);
	SinFlat			sinFlat(a);
	SinPositive		sinPositive(a);
	Linear			line(a, 0.0, 5.0);
	Linear			minus(a, 0.0, -1.0);
	Square			square(a, 0.4, 3);
	Triangle		triangle(a, 0.4, 3);
	Step			step(a, 5);
	RandUniform		rUniform(a, 5);
	RandNormal		rNormal(a);

	mulOP1.AddInput(sinOp.Get()).AddInput(minus.Get()).Execute();

	sumOP.AddInput(sinFlat.Get())
		 .AddInput(mulOP1.GetOutput()).Execute();
	

	mulOP.AddInput(sumOP.GetOutput())
		 .AddInput(line.Get()).Execute();

	sumOP1.AddInput(mulOP.GetOutput())
		  .AddInput(sinFlat.Get()).Execute();

	PutToFile(sumOP1.GetOutput());




	Number comp(1, 2);
	Number comp1(3, 3);

	Number sum = comp + comp1;

	Number real(1);

	sum += real;

	cout << "XD" << endl;
}