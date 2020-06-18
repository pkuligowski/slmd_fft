#include "systemc.h"
#include "fft.h"
#include "window.h"
#include "source.h"
#include "sink.h"

int sc_main(int, char*[])
{
	sc_signal<float> in_data;
	sc_signal<bool> in_data_ready;
	sc_signal<bool> window_data_ready;
	sc_signal<bool> fft_data_received;
	sc_signal<float> window_data;
	sc_signal<float> fft_data;
	sc_signal<bool> in_data_request;
	sc_signal<bool> window_data_request;
	sc_signal<bool> fft_data_ready;

	sc_clock clock("TAKTOWANIE", 10, SC_NS, 0.5, 0.0, SC_NS);

	source SOURCE1("WCZYTYWANIE");
	SOURCE1.out_data_request(in_data_request);
	SOURCE1.out_data(in_data);
	SOURCE1.out_data_ready(in_data_ready);
	SOURCE1.CLK(clock);

	window WINDOW1("OKNO");
	WINDOW1.in_data(in_data);
	WINDOW1.in_data_ready(in_data_ready);
	WINDOW1.in_data_request(in_data_request);
	WINDOW1.out_data_request(window_data_request);
	WINDOW1.out_data(window_data);
	WINDOW1.out_data_ready(window_data_ready);
	WINDOW1.CLK(clock);

	fft FFT1("FFT"); 
	FFT1.in_data(window_data);
	FFT1.in_data_ready(window_data_ready);
	FFT1.in_data_request(window_data_request);
	FFT1.out_data_received(fft_data_received);
	FFT1.out_data(fft_data);
	FFT1.out_data_ready(fft_data_ready);
	FFT1.CLK(clock);

	sink SINK1("ZAPIS");
	SINK1.in_data_ready(fft_data_ready);
	SINK1.in_data_received(fft_data_received);
	SINK1.in_data(fft_data);
	SINK1.CLK(clock);

	sc_start();
	return 0;
}
