struct sink: sc_module {
	sc_in<bool>  in_data_ready; 
	sc_out<bool> in_data_received;
	sc_in<float> in_data;
	sc_in_clk    CLK;

	FILE* plik_wyjsciowy;

	SC_CTOR(sink)
	{
		SC_CTHREAD(entry, CLK.pos());
	}

	void entry(); 

	~sink()
	{
		fclose(plik_wyjsciowy);
	}
};
