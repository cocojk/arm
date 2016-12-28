/* ____________________________________________________________________
 *
 * Copyright (c) 2003, Andrew N. Sloss, Dominic Symes, Chris Wright
 * All rights reserved.
 * ____________________________________________________________________
 * 
 * NON-COMMERCIAL USE License
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 *
 * 1. For NON-COMMERCIAL USE only.
 * 
 * 2. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 3. Redistributions in binary form must reproduce the above 
 *    copyright notice, this list of conditions and the following 
 *    disclaimer in the documentation and/or other materials provided 
 *    with the distribution. 
 *
 * 4. All advertising materials mentioning features or use of this 
 *    software must display the following acknowledgement:
 *
 *    This product includes software developed by Andrew N. Sloss,
 *    Chris Wright and Dominic Symes. 
 *
 *  THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
 *  OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 *  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 *  OF SUCH DAMAGE. 
 *
 * If you have questions about this license or would like a different
 * license please email : andrew@sloss.net
 *
 * Reference code for examples of section 7.4
 */
 
#include "ch07test.h"
#include <math.h>

unsigned usqr_simple(unsigned d, unsigned N)
{
  unsigned t, q=0, r=d;
  
  do
  {                     /* calculate next quotient bit */
    N--;                /* move down to next bit */
    t = 2*q+(1<<N);     /* new r = old r - (t<<N) */
    if ( (r>>N) >= t )  /* if (r >= (t<<N)) */
    {
      r -= (t<<N);      /* update remainder */
      q += (1<<N);      /* update root */
    }
  } while (N);
  
  return q;
}

int32 usqr_simple_test(int32 a)
{
  return usqr_simple((unsigned)a,16);
}

int32 ref_usqr_32(int32 a)
{
  uint32 d = a;
  int N=16;
  uint32 q=0,q1;
  
  do
  {
    N--;
    q1 = q+((uint32)1<<N);
    if (d >= q1*q1)
    {
      q=q1;
    }
  } while (N);
  
  return q;
}

int32 ref_ucbr_32(int32 a)
{
  uint32 d = a;
  int N=11;
  uint32 q=0,q1;
  
  do
  {
    N--;
    q1 = q+((uint32)1<<N);
    /* NB (int)(2^(32/3))=17=1625 */
    if (q1 <= 1625 && d >= q1*q1*q1)
    {
      q=q1;
    }
  } while (N);
  
  return q;
}

int32 ref_rsqr_32(int32 a)
{
  double d=(double)(uint32)a;
  
  if (a==0)
  {
    return 0x7FFFFFFF;
  }
  d = (double)(1u<<31)/sqrt(d);

  return (int32)(d+0.5);
}
