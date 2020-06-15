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

  source.cpp - This is the implementation file for the synchronous process
               "source" .

  Original Author: Rashmi Goswami, Synopsys, Inc.

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/


#include "systemc.h"
#include "source_stdin.h"

void source_stdin::entry()
{
  float tmp_val;
  out_data_valid.write(false);

  while(true)
  { 
    do { wait(); } while ( !(out_data_req == true) );
	cin >> tmp_val;
	//if (line == "Done...")
    //  { cout << "End of Input Stream: Simulation Stops" << endl;
    //    sc_stop();
    //    break;
	//};
    out_real.write(tmp_val);
	cout << tmp_val;
	out_imag.write(0);
    out_data_valid.write(true);
    do { wait(); } while ( !(out_data_req == false) );
    out_data_valid.write(false);
    wait();
  }
}
