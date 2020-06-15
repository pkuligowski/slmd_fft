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

  sink.cpp - This is the implementation file for the synchronous process
             "sink".

  Original Author: Rashmi Goswami, Synopsys, Inc.

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/


#include "systemc.h"
#include "sink_zmq.h"

void sink_zmq::entry()
{

 in_data_ack.write(false);

 while(true)
 { 
   do { wait(); } while ( !(in_data_ready == true) );
   //fprintf(fp_real,"%e  \n",in_real.read());
   //fprintf(fp_imag,"%e  \n",in_imag.read());
   cout << "D|" << in_real.read() << endl;
   in_data_ack.write(true);
   do { wait(); } while ( !(in_data_ready == false) );
   in_data_ack.write(false); 
 }
}
