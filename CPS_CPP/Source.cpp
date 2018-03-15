#include <iostream>
#include "Complex.h"
#include "BasicGenerator.h"
#include "Sum.h"
#include "Multiply.h"
#include "Sinus.h"


using namespace std;

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

	//Tworze jakikolwiek JSON
	cout << '{';
	cout << multi << endl;
	cout << "type: \"scatter\"";
	cout << '}';
}