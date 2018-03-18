#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "Complex.h"
#include "Number.h"
#include "Linear.h"
#include "Sum.h"
#include "Sampler.h"
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
	Sum sumOP{};
	Sin sinOp(Sampler(0, 0.1, 10));
	SinFlat sinFlat(Sampler(0, 0.1, 10));
	SinPositive sinPositive(Sampler(0, 0.1, 10));
	Linear line(Sampler(0, 0.1, 10), 0.0, 5.0);
	Square square(Sampler(0, 0.01, 10), 0.4, 3);
	Triangle triangle(Sampler(0, 0.01, 10), 0.4, 3);
	Step step(Sampler(0, 0.01, 10), 5);
	RandUniform rUniform(Sampler(0, 0.01, 10), 5);
	RandNormal rNormal(Sampler(0, 0.01, 10));

	auto XD = sumOP.AddInput(sinOp.Get())
				   .AddInput(sinPositive.Get()).Execute().GetOutput();

	PutToFile(rUniform.Get());

	Number comp(1, 2);
	Number comp1(3, 3);

	Number sum = comp + comp1;

	Number real(1);

	sum += real;

	cout << "XD" << endl;
}