#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "Complex.h"
#include "Number.h"

#include "Average.h"
#include "AverageMod.h"
#include "Power.h"
#include "RMS.h"
#include "Variance.h"
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
#include "Impulse.h"
#include "ImpulseNoise.h"
#include "Histogram.h"
#include "FromFile.h"

using namespace std;
using namespace Numeric;
using namespace Base;
using namespace Operation;
using namespace Generator;

void PutToFile(const Base::Data& aOutput, const std::string& aName = "", const std::string& aType = "")
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
	if (aName.empty())
	{
		ss << "_" << value;
	}
	else
	{
		ss << '_' << aName;
	}
	ss << ".json";

	fstream file;
	file.open(ss.str(), fstream::out);
	if (file.is_open())
	{
		file << '{' << '\n';
		file << aOutput << endl;
		if (!aType.empty())
		{
			file << "\"type\": \"" << aType << "\"," << '\n';
		}
		else
		{
			file << "\"type\": \"scatter\"," << '\n';
		}
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
	//FromFile		fileRead("../QuickDisplay/data/dupa.json");
	Average			avg{};
	AverageMod		avgMod{};
	Power			pwr{};
	Variance		variance{};
	RMS				rms{};
	Histogram		histogram(0.1);

	Sampler a(0, 0.01, 9);

	Sin				sinOp(a, 1.0);
	SinFlat			sinFlat(a, 2.0);
	SinPositive		sinPositive(a, 2.0);
	Linear			line(a, 0.0, 5.0);
	Linear			minus(a, 0.0, -1.0);
	Square			square(a, 0.4, 3);
	Triangle		triangle(a, 0.4, 3);
	Step			step(a, 5);
	RandUniform		rUniform(a, 5);
	RandNormal		rNormal(a);
	Impulse			impulse(a, 12);
	ImpulseNoise    impulseNoise(a, 0.1);

	//fileRead.Generate();

	sinOp.Generate();
	PutToFile(sinOp.GetOutput(), "SIN");

	//sinFlat.Generate();
	//PutToFile(sinFlat.GetOutput());

	//sinPositive.Generate();
	//PutToFile(sinPositive.GetOutput());

	/*line.Generate();
	PutToFile(line.GetOutput());

	minus.Generate();
	PutToFile(minus.GetOutput());

	square.Generate();
	PutToFile(square.GetOutput());

	triangle.Generate();
	PutToFile(triangle.GetOutput());

	step.Generate();
	PutToFile(step.GetOutput());

	rUniform.Generate();
	PutToFile(rUniform.GetOutput());

	rNormal.Generate();
	PutToFile(rNormal.GetOutput());

	impulse.Generate();
	PutToFile(impulse.GetOutput());

	impulseNoise.Generate();
	PutToFile(impulseNoise.GetOutput());*/

	avg.AddInput(sinOp).Execute();
	PutToFile(avg.GetOutput(), "AVG");

	avgMod.AddInput(sinOp).Execute();
	PutToFile(avgMod.GetOutput(), "AVGMOD");

	variance.AddInput(sinOp).Execute();
	PutToFile(variance.GetOutput(), "VARIANCE");

	rms.AddInput(sinOp).Execute();
	PutToFile(rms.GetOutput(), "RMS");

	pwr.AddInput(sinOp).Execute();
	PutToFile(pwr.GetOutput(), "POWER");

	histogram.AddInput(sinOp).Execute();
	PutToFile(histogram.GetOutput(), "HISTOGRAM", "bar");

	/*mulOP1.AddInput(sinOp).AddInput(minus).Execute();

	sumOP.AddInput(sinFlat)
		 .AddInput(mulOP1.Execute()).Execute();
	

	mulOP.AddInput(sumOP.Execute())
		 .AddInput(line).Execute();

	sumOP1.AddInput(mulOP.Execute())
		  .AddInput(sinFlat).Execute();

	PutToFile(sumOP1.GetOutput());*/




	Number comp(1, 2);
	Number comp1(3, 3);

	Number sum = comp + comp1;

	Number real(1);

	sum += real;

	cout << "XD" << endl;
}