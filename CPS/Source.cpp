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

#include "DFT.h"
#include "IDFT.h"
#include "FFT_DIT.h"
#include "FFT_DIF.h"

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
	/*{
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
	}*/

	// Filtracja... nie mam pojecia...
	//{
	//	Sampler	   sampler(0, 0.01, 10.0);
	//	Sin		   sin(sampler, 1, 1.0);
	//	sin.Generate();

	//	RandNormal noise(sampler);
	//	noise.Generate();

	//	Convolution conv;
	//	conv.AddInput(sin).AddInput(noise).Execute();
	//	{
	//		ToFile f("Filtr_sygnal");
	//		f.AddInput(conv).Execute();
	//	}
	//	{
	//		// Filtr górnoprzepustowy z oknem Prostokatnym
	//		// N=200, K=10, M=10 
	//		Filter<FilterType::Up, Prostokatne>    filter(200, 10, 10);
	//		filter.AddInput(conv).Execute();
	//		ToFile f("filtr_UP_Prostokatne");
	//		f.AddInput(filter).Execute();
	//	}
	//	{
	//		// Filtr środkowoprzepustowy z oknem Blackmana
	//		// N=50, K=8, M=20
	//		Filter<FilterType::Middle, Blackman>    filter(50, 8, 20);
	//		filter.AddInput(conv).Execute();
	//		ToFile f("filtr_MID_Blackman");
	//		f.AddInput(filter).Execute();
	//	}
	//	{
	//		// Filtr środkowoprzepustowy z oknem Blackmana
	//		// N=80, K=8, M=20
	//		Filter<FilterType::Down, Hamming>    filter(80, 8, 20);
	//		filter.AddInput(conv).Execute();
	//		ToFile f("filtr_Down_Hamming");
	//		f.AddInput(filter).Execute();
	//	}
	//	{
	//		// Filtr środkowoprzepustowy z oknem Hanna (Hanning'a)
	//		// N=50, K=8, M=20
	//		Filter<FilterType::Up, Hanna>    filter(50, 8, 20);
	//		filter.AddInput(conv).Execute();
	//		ToFile f("filtr_UP_Hanna");
	//		f.AddInput(filter).Execute();
	//	}
	//}

	// To z radarem - korelacja
	/*{
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
		}*/

		/*
		  sinOpMoved jest przesunięty
		  o 0.25. Próbkowanie jest ustawione na 0.05.
		  Więc przesuwamy o równo 5 próbek.

		  Korelacja powinna wypluć sygnał, którego maximum jest przesunięte
		  względem środka wszystkich próbek o 5.
		  Tak też robi.
		*/
		/*	{
				Correlation corr;
				corr.AddInput(sinOp).AddInput(sinOpMoved).Execute();
				ToFile f("Radar_wyjscie", "korelacja");
				f.AddInput(corr).Execute();
			}
		}*/

		// ZADANIE 4 - DFT

	Numeric::Number a(1.0, 1.0);
	Numeric::Number b(2.0, 2.0);

	a /= b;

	Numeric::Number c = a / b;


	// Sygnał S(1) do zadania.
	Sum sygnal{};
	{
		constexpr double PI = 3.141592653589793238;
		Sampler sampler(0, 0.015625, 3.99999999);
		Sin		sin1(sampler, 2.0, 2.0, PI/2.0);
		Sin     sin2(sampler, 0.5, 5.0, PI/2.0);

		sin1.Generate();
		sin2.Generate();
		sygnal.AddInput(sin1).AddInput(sin2).Execute();

		ToFile out("sygnal");
		out.AddInput(sygnal).Execute();
	}



	{
		DFT		   dft;
		dft.AddInput(sygnal).Execute();
		{
			ToFile out("dft");
			out.AddInput(dft).Execute();
		}
		
		{
			IDFT		idft;
			idft.AddInput(dft).Execute();

			ToFile out("idft_DFT");
			out.AddInput(idft).Execute();
		}

		FFT_DIT		fft_dit;
		fft_dit.AddInput(sygnal).Execute();
		{
			ToFile out("fft_dit");
			out.AddInput(fft_dit).Execute();
		}

		{
			IDFT		idft;
			idft.AddInput(fft_dit).Execute();

			ToFile out("idft_fft_dit");
			out.AddInput(idft).Execute();
		}

	}


}