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

  fft.cpp - This is the implementation file for the synchronous process "fft".

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
#include "math.h"

void fft::entry()
{
  float sample[4096][2];
  unsigned int index;

  while(true)
  { data_req.write(false);
    data_ready.write(false);
    index = 0;
    //Reading in the Samples
      cout << endl << "Reading in the samples..." << endl;
      while( index < 4096 )
      {
       data_req.write(true);
       do { wait(); } while (data_valid == true);
       sample[index][0] = in_real.read();
       sample[index][1] = in_imag.read();
       index++;
       data_req.write(false);
       wait();
      }
      index = 0;


      //////////////////////////////////////////////////////////////////////////
      ///  Computation - 1D Complex DFT In-Place DIF Computation Algorithm  ////
      //////////////////////////////////////////////////////////////////////////
    
      //Size of FFT, N = 2**M    
       unsigned int N, M, len ;  
       float theta; 
	   float W[2048][2], w_real, w_imag, w_rec_real, w_rec_imag, w_temp;

       //Initialize
	   M = 12; N = 4096;
       len = N/2;
       theta = 8.0*atan(1.0)/N;

       cout << "Computing..." << endl;

       //Calculate the W-values recursively
        w_real =  cos(theta);
        w_imag =  -sin(theta);

        w_rec_real = 1;
        w_rec_imag = 0;

        index = 0;    
        while(index < len-1) 
        {
           w_temp = w_rec_real*w_real - w_rec_imag*w_imag;
           w_rec_imag =  w_rec_real*w_imag + w_rec_imag*w_real;
           w_rec_real = w_temp;
           W[index][0] = w_rec_real;
           W[index][1] = w_rec_imag;
           index++;
        }


       float tmp_real, tmp_imag, tmp_real2, tmp_imag2;
       unsigned int stage, i, j,index2, windex, incr;
     
      //Begin Computation 
       stage = 0;

       len = N;
       incr = 1;

       while (stage < M)
       { 
        len = len/2;
 
        //First Iteration :  With No Multiplies
          i = 0;
 

          while(i < N)
          {
             index =  i; index2 = index + len; 
             
             tmp_real = sample[index][0] + sample[index2][0];
             tmp_imag = sample[index][1] + sample[index2][1];
 
             sample[index2][0] = sample[index][0] - sample[index2][0];
             sample[index2][1] = sample[index][1] - sample[index2][1];

             sample[index][0] = tmp_real;
             sample[index][1] = tmp_imag;
        

             i = i + 2*len;          
 
          }


        //Remaining Iterations: Use Stored W
         j = 1; windex = incr - 1;
         while (j < len) // This loop executes N/2 times at first stage, .. once at last stage.
         {
            i = j; 
            while (i < N)
            {
              index = i;
              index2 = index + len;

              tmp_real = sample[index][0] + sample[index2][0]; 
              tmp_imag = sample[index][1] + sample[index2][1];
              tmp_real2 = sample[index][0] - sample[index2][0];
              tmp_imag2 = sample[index][1] - sample[index2][1];
  
              sample[index2][0] = tmp_real2*W[windex][0] - tmp_imag2*W[windex][1];
              sample[index2][1] = tmp_real2*W[windex][1] + tmp_imag2*W[windex][0]; 

              sample[index][0] = tmp_real;
              sample[index][1] = tmp_imag;
           
              i = i + 2*len;
              
            }
            windex = windex + incr;
            j++;
         }
          stage++;
          incr = 2*incr;
       } 
           
     //////////////////////////////////////////////////////////////////////////
     
     //Writing out the normalized transform values in bit reversed order
      sc_uint<12> bits_i;
      sc_uint<12> bits_index;
      bits_i = 0;
      i = 0;

      cout << "Writing the transform values..." << endl;
	  while (i < 1024)
      {
       bits_i = i;
	   bits_index[11]= bits_i[0];
	   bits_index[10]= bits_i[1];
       bits_index[9]= bits_i[2];
       bits_index[8]= bits_i[3];
       bits_index[7]= bits_i[4];
       bits_index[6]= bits_i[5];
	   bits_index[5]= bits_i[6];
	   bits_index[4]= bits_i[7];
	   bits_index[3]= bits_i[8];
	   bits_index[2]= bits_i[9];
	   bits_index[1]= bits_i[10];
	   bits_index[0]= bits_i[11];
       index = bits_index;
       out_real.write(sample[index][0]);
       out_imag.write(sample[index][1]);
       data_ready.write(true);
       do { wait(); } while ( !(data_ack == true) );
       data_ready.write(false);
       i++;
       wait();
      }
      index = 0; 
      cout << "Done..." << endl;
  }
 }
