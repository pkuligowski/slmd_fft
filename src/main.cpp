/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2014 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.accellera.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  main.cpp - This file instantiates all processes and ties them together
             with signals.

  Original Author: Rashmi Goswami, Synopsys, Inc.

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/


#include "systemc.h"
#include "fft.h"
#include "window.h"
#include "source.h"
#include "sink.h"

int sc_main(int , char*[])
{
 sc_signal<float> in_real;
 sc_signal<float> in_imag;
 sc_signal<bool> in_data_valid;
 sc_signal<bool> window_data_valid;
 sc_signal<bool> fft_data_ack;
 sc_signal<float> window_real;
 sc_signal<float> window_imag;
 sc_signal<float> fft_real;
 sc_signal<float> fft_imag;
 sc_signal<bool> in_data_req;
 sc_signal<bool> window_data_req;
 sc_signal<bool> fft_data_ready;

 sc_clock clock("CLOCK", 10, SC_NS, 0.5, 0.0, SC_NS);

 source SOURCE1("SOURCEPROCESS");
 SOURCE1.out_data_req(in_data_req);
 SOURCE1.out_real(in_real);
 SOURCE1.out_imag(in_imag);
 SOURCE1.out_data_valid(in_data_valid);
 SOURCE1.CLK(clock);

 window WINDOW1("WINDOWPROCESS");
 WINDOW1.in_real(in_real);
 WINDOW1.in_imag(in_imag);
 WINDOW1.in_data_valid(in_data_valid);
 WINDOW1.in_data_req(in_data_req);

 WINDOW1.out_data_req(window_data_req);
 WINDOW1.out_real(window_real);
 WINDOW1.out_imag(window_imag);
 WINDOW1.out_data_valid(window_data_valid);
 WINDOW1.CLK(clock);

 fft FFT1("FFTPROCESS"); 
 FFT1.in_real(window_real);
 FFT1.in_imag(window_imag);
 FFT1.in_data_valid(window_data_valid);
 FFT1.in_data_req(window_data_req);
 FFT1.out_data_ack(fft_data_ack);
 FFT1.out_real(fft_real);
 FFT1.out_imag(fft_imag);
 FFT1.out_data_ready(fft_data_ready);
 FFT1.CLK(clock);

 sink SINK1("SINKPROCESS");
 SINK1.in_data_ready(fft_data_ready);
 SINK1.in_data_ack(fft_data_ack);
 SINK1.in_real(fft_real);
 SINK1.in_imag(fft_imag);
 SINK1.CLK(clock);

 sc_start();
 return 0;

}
