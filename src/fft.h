struct fft: sc_module {
	sc_in<float> in_data;
	sc_in<bool> in_data_ready; 
	sc_in<bool> out_data_received;   
	sc_out<float> out_data;
	sc_out<bool> in_data_request;         
	sc_out<bool> out_data_ready;       
	sc_in_clk CLK;

 
	SC_CTOR(fft)
	{
		SC_CTHREAD(entry, CLK.pos());
    }

	void entry();  
};      


