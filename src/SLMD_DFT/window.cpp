#include "systemc.h"
#include "window.h"
#include "math.h"
#include "config.h"
#include "window_hamming.h"
#include "window_blackman.h"


void window::entry()
{
	float probki[LICZBA_PROBEK];
	unsigned int index;

	while (true)
	{
		index = 0;
		in_data_request.write(false);
		out_data_ready.write(false);

		while (index < LICZBA_PROBEK)
		{
			in_data_request.write(true);
			do { wait(); } while (!(in_data_ready == false));
			probki[index] = in_data.read();
			index++;
			in_data_request.write(false);
			wait();
		}

		index = 0;
		while (index < LICZBA_PROBEK)
		{
			out_data.write(probki[index] * WINDOW_HAMMING[index]);
			out_data_ready.write(true);
			while (out_data_request)
			{
				wait();
			}
			out_data_ready.write(false);
			index++;
			wait();
		}
	}
}
