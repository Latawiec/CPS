﻿#include <iostream>
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
#include "ToFile.h"
#include "RandNormal.h"
#include "RandUniform.h"
#include "Impulse.h"
#include "ImpulseNoise.h"
#include "Histogram.h"
#include "FromFile.h"

#include "SignalSampler.h"
#include "ReconstructZeroOrder.h"
#include "ReconstructFirstOrder.h"
#include "QuantizeCut.h"
#include "QuantizeTreshold.h"
#include "MSE.h"
#include "SNR.h"
#include "PSNR.h"
#include "MD.h"

using namespace std;
using namespace Numeric;


int main()
{
	ToFile			fileOP{};
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

	Sampler a(0, 0.001, 2.0);

	Sin				sinOp(a, 1, 2.0);
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

	SignalSampler	sigSampler(100);
	ReconstructZeroOrder recZero(a);
	ReconstructFirstOrder recFirst(a);
	QuantizeCut quantizeCut(0.2);
	QuantizeThreshold quantizeTreshold(1);
	MSE mse{};
	SNR snr{};
	PSNR psnr{};
	MD md;

	
	//Tworzymy sobie sinus...
	sinOp.Generate();
	// I myk do pliku.
	fileOP.AddInput(sinOp).Execute();
	
	//Próbkujemy go ...
	sigSampler.AddInput(sinOp).Execute();
	// I myk do pliku
	fileOP.AddInput(sigSampler).Execute();

	//Odtwarzamy go przez ZeroOrder...
	recZero.AddInput(sigSampler).Execute();
	//I myk do pliku!
	fileOP.AddInput(recZero).Execute();

	//Odtwarzamy go przez FirstOrder...
	recFirst.AddInput(sigSampler).Execute();
	//I myk do pliku!
	fileOP.AddInput(recFirst).Execute();

	//Kwantujemy sobie sinusa ..
	quantizeCut.AddInput(sinOp).Execute();
	//I myyyyyyyk!
	fileOP.AddInput(quantizeCut).Execute();

	//Kwantujemy sobie sinusa ale tego średniego
	quantizeTreshold.AddInput(sinOp).Execute();
	//I myyyyyyyk!
	fileOP.AddInput(quantizeTreshold).Execute();

	//licząc MSE musimy mieć wartości i wartości docelowe... dodajemy obydwie
	mse.AddInput(quantizeTreshold).AddInput(sinOp).Execute();
	//Do pliku
	fileOP.AddInput(mse).Execute();

	// snr - cokolwiek to jest...
	snr.AddInput(quantizeTreshold).AddInput(sinOp).Execute();
	fileOP.AddInput(snr).Execute();

	// max difference MD 
	md.AddInput(quantizeTreshold).AddInput(sinOp).Execute();
	fileOP.AddInput(md).Execute();

	//PSNR
	psnr.AddInput(quantizeTreshold).AddInput(sinOp).Execute();
	fileOP.AddInput(psnr).Execute();

	//fileRead.Generate();

	sinOp.Generate();
	fileOP.AddInput(sinOp);
	fileOP.Execute();

	sinFlat.Generate();
	fileOP.AddInput(sinFlat);
	fileOP.Execute();

	sinPositive.Generate();
	fileOP.AddInput(sinPositive);
	fileOP.Execute();

	line.Generate();
	fileOP.AddInput(line);
	fileOP.Execute();

	minus.Generate();
	fileOP.AddInput(minus);
	fileOP.Execute();

	square.Generate();
	fileOP.AddInput(square);
	fileOP.Execute();

	triangle.Generate();
	fileOP.AddInput(triangle);
	fileOP.Execute();

	step.Generate();
	fileOP.AddInput(step);
	fileOP.Execute();

	rUniform.Generate();
	fileOP.AddInput(rUniform);
	fileOP.Execute();

	rNormal.Generate();
	fileOP.AddInput(rNormal);
	fileOP.Execute();

	impulse.Generate();
	fileOP.AddInput(impulse);
	fileOP.Execute();

	impulseNoise.Generate();
	fileOP.AddInput(impulseNoise);
	fileOP.Execute();

	avg.AddInput(sinOp).Execute();
	fileOP.AddInput(avg);
	fileOP.Execute();

	avgMod.AddInput(sinOp).Execute();
	fileOP.AddInput(avgMod);
	fileOP.Execute();

	variance.AddInput(sinOp).Execute();
	fileOP.AddInput(variance);
	fileOP.Execute();

	rms.AddInput(sinOp).Execute();
	fileOP.AddInput(rms);
	fileOP.Execute();

	pwr.AddInput(sinOp).Execute();
	fileOP.AddInput(pwr);
	fileOP.Execute();

	histogram.AddInput(sinOp).Execute();
	fileOP.AddInput(histogram);
	fileOP.Execute();

	mulOP1.AddInput(sinOp).AddInput(minus).Execute();

	mulOP1.Execute();
	sumOP.AddInput(sinFlat)
		 .AddInput(mulOP1).Execute();
	
	sumOP.Execute();
	mulOP.AddInput(sumOP)
		 .AddInput(line).Execute();

	mulOP.Execute();
	sumOP1.AddInput(mulOP)
		  .AddInput(sinFlat).Execute();

	fileOP.AddInput(sumOP1);
	fileOP.Execute();
	
	Number comp(1, 2);
	Number comp1(3, 3);

	Number sum = comp + comp1;

	Number real(1);

	sum += real;

	cout << "XD" << endl;
}