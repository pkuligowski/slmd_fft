#include "systemc.h"
#include "fft.h"
#include "config.h"
#include <math.h>
#include <complex>
#include <valarray>

typedef std::complex<double> Zespolona;
typedef std::valarray<Zespolona> Tablica;


void licz_fft(Tablica& x)
{
	unsigned int N = x.size();

	if (N == 1){
		return;
	}

	Tablica parz = x[std::slice(0, N/2, 2)];
	Tablica  nieparz = x[std::slice(1, N/2, 2)];
	Zespolona t;

	licz_fft(nieparz);
	licz_fft(parz);
	
	double wspolczynnik = -6.283185307179586/N;
	for (unsigned int k=0; k<(N/2); ++k)
	{
		t = std::polar(1.0, wspolczynnik*k) * nieparz[k];
		x[k] = t+parz[k];
		x[k+N/2] = parz[k]-t;
	}
}


void fft::entry()
{
  unsigned int i;
  Zespolona probki[LICZBA_PROBEK];

  while(true)
  {
	in_data_request.write(false);
    out_data_ready.write(false);
    i = 0;

    cout << "Odczyt probek >> ";
	while (i < LICZBA_PROBEK)
    {
		in_data_request.write(true);
        do {
			wait();
		} while (in_data_ready == false);

		probki[i] = in_data.read();
        i++;
        in_data_request.write(false);
        wait();
    }
    i = 0;
	
	cout << "Obliczanie FFT >> ";
	Tablica data(probki, LICZBA_PROBEK);
	
	licz_fft(data);

	cout << "Zapis FFT >> " ;
	for (int i = 0; i < (LICZBA_PROBEK/4); i++)
	{
		out_data.write(data[i].real());
		out_data_ready.write(true);

		while (!(out_data_received == true))
		{
			wait();
		}
		out_data_ready.write(false);

		wait();
	}

	cout << "Gotowe!" << endl;
  }
 }
