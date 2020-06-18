#include "systemc.h"
#include "sink.h"

void sink::entry()
{
	plik_wyjsciowy = fopen("fft", "w");
	in_data_received.write(false);

	while (true)
	{
		WAIT_UNTIL(in_data_ready == true);
		fprintf(plik_wyjsciowy, "%.8f\n", in_data.read());

		in_data_received.write(true);
		WAIT_UNTIL(in_data_ready == false);
		in_data_received.write(false);
	}
}
