#include "systemc.h"
#include "window.h"
#include "math.h"
#include "window_hamming.h"
#include "window_blackman.h"

void window::entry()
{
	float sample[4096][2];
	unsigned int index;

	while (true)
	{
		index = 0;
		in_data_req.write(false);
		out_data_valid.write(false);

		cout << endl << "Window is reading the samples..." << endl;
		while (index < 4096)
		{
			in_data_req.write(true);
			do { wait(); } while (!(in_data_valid == false));
			sample[index][0] = in_real.read();
			sample[index][1] = in_imag.read();
			index++;
			in_data_req.write(false);
			wait();
		}

		index = 0;
		while (index < 4096)
		{
			out_real.write(sample[index][0] * WINDOW_BLACKMAN[index]);
			out_imag.write(sample[index][1]);
			out_data_valid.write(true);
			do { wait(); } while (!(out_data_req == false));
			out_data_valid.write(false);
			index++;
			wait();
		}
	}
}
