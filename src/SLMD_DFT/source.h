struct source: sc_module {
  sc_in<bool> out_data_request; 
  sc_out<float> out_data;
  sc_out<bool> out_data_ready;
  sc_in_clk    CLK;

  SC_CTOR(source)
  {
	SC_CTHREAD(entry, CLK.pos());
  }

 void entry();
};
