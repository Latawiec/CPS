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

#include "Convolution.h"
#include "Correlation.h"
#include "Filter.h"

using namespace std;
using namespace Numeric;


int main()
{
	//ToFile			fileOP{};
	//Sum				sumOP{};
	//Sum				sumOP1{};
	//Divide			divOP{};
	//Multiply		mulOP{};
	//Multiply		mulOP1{};
	//Subtract		subOP{};
	//FromFile		fileRead("../QuickDisplay/data/dupa.json");
	//Average			avg{};
	//AverageMod		avgMod{};
	//Power			pwr{};
	//Variance		variance{};
	//RMS				rms{};
	//Histogram		histogram(0.1);

	//Sampler a(0, 0.05, 5.0);

	//Sin				sinOp(a, 1, 2.0);
	//Sin				sinOpMoved(a, 1, 2.0, 0.25);
	//SinFlat			sinFlat(a, 2.0);
	//SinPositive		sinPositive(a, 2.0);
	//Linear			line(a, 0.0, 0.0);
	//Linear			minus(a, 0.0, -1.0);
	//Square			square(a, 0.4, 3);
	//Triangle		triangle(a, 0.4, 3);
	//Step			step(a, 5);
	//RandUniform		rUniform(a, 5);
	//RandNormal		rNormal(a);
	//Impulse			impulse(a, 12);
	//ImpulseNoise    impulseNoise(a, 0.1);

	//SignalSampler	sigSampler(100);
	//ReconstructZeroOrder recZero(a);
	//ReconstructFirstOrder recFirst(a);
	//QuantizeCut quantizeCut(0.2);
	//QuantizeThreshold quantizeTreshold(1);
	//MSE mse{};
	//SNR snr{};
	//PSNR psnr{};
	//MD md;

	//Convolution conv;
	//Correlation corr;
	//Filter<FilterType::Up, Blackman>    filter(200, 10, 10);

// ZADANIE 3

	// Jakiś tam splot. Nie wiem co tu ciekawego...
	{
		Sampler	   sampler(0, 0.01, 10.0);
		Sin		   sin(sampler, 1, 1.0);
		RandNormal noise(sampler);
		{
			sin.Generate();
			ToFile f("Sinus_splot");
			f.AddInput(sin).Execute();
		}
		{
			noise.Generate();
			ToFile f("Szum_splot");
			f.AddInput(noise).Execute();
		}
		{
			Convolution conv;
			conv.AddInput(sin).AddInput(noise).Execute();
			ToFile f("Splot");
			f.AddInput(conv).Execute();
		}
	}

	// Filtracja... nie mam pojecia...
	{
		Sampler	   sampler(0, 0.01, 20.0);
		Sin		   sin(sampler, 1, 1.0);
		{
			sin.Generate();
			ToFile f("Filtr_sygnal");
			f.AddInput(sin).Execute();
		}
		{
			// Filtr górnoprzepustowy z oknem Prostokatnym
			// N=200, K=10, M=10 
			Filter<FilterType::Up, Prostokatne>    filter(200, 10, 10);
			filter.AddInput(sin).Execute();
			ToFile f("filtr_UP_Prostokatne");
			f.AddInput(filter).Execute();
		}
		{
			// Filtr środkowoprzepustowy z oknem Blackmana
			// N=50, K=8, M=20
			Filter<FilterType::Middle, Blackman>    filter(50, 8, 20);
			filter.AddInput(sin).Execute();
			ToFile f("filtr_MID_Blackman");
			f.AddInput(filter).Execute();
		}
		{
			// Filtr środkowoprzepustowy z oknem Blackmana
			// N=80, K=8, M=20
			Filter<FilterType::Down, Hamming>    filter(80, 8, 20);
			filter.AddInput(sin).Execute();
			ToFile f("filtr_Down_Hamming");
			f.AddInput(filter).Execute();
		}
		{
			// Filtr środkowoprzepustowy z oknem Hanna (Hanning'a)
			// N=50, K=8, M=20
			Filter<FilterType::Up, Hanna>    filter(50, 8, 20);
			filter.AddInput(sin).Execute();
			ToFile f("filtr_UP_Hanna");
			f.AddInput(filter).Execute();
		}
	}

	// To z radarem - korelacja
	{
		Sampler sampler(0, 0.05, 5.0);

		Sin		sinOp(sampler, 1, 2.0);
		Sin		sinOpMoved(sampler, 1, 2.0, 0.25);
		{

			sinOp.Generate();
			ToFile f("Sinus_normalny", "normalny");
			f.AddInput(sinOp).Execute();
		}
		{
			sinOpMoved.Generate();
			ToFile f("Sinus_przesuniety", "przesuniety");
			f.AddInput(sinOpMoved).Execute();
		}
		
		/*
		  sinOpMoved jest przesunięty
		  o 0.25. Próbkowanie jest ustawione na 0.05.
		  Więc przesuwamy o równo 5 próbek. 

		  Korelacja powinna wypluć sygnał, którego maximum jest przesunięte
		  względem środka wszystkich próbek o 5.
		  Tak też robi.
		*/
		{
			Correlation corr;
			corr.AddInput(sinOp).AddInput(sinOpMoved).Execute();
			ToFile f("Radar_wyjscie", "korelacja");
			f.AddInput(corr).Execute();
		}
	}

}