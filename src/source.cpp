#include "systemc.h"
#include "source.h"


void source::entry()
{
	FILE *fp_real;
	float probka;

	fp_real = fopen("samples", "r");

	out_data_ready.write(false);

	while(true)
	{ 
		WAIT_UNTIL(out_data_request == true);

		if (fscanf(fp_real,"%f\n",&probka) == EOF)
		{
			cout << "Koniec pliku" << endl;
			sc_stop();
			break;
		};
		out_data.write(probka);
		out_data_ready.write(true);

		WAIT_UNTIL(out_data_request == false);

		out_data_ready.write(false);
		wait();
  }
}
