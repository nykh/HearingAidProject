/*
 * rand.c
 *
 * Code generation for function 'rand'
 *
 * C source code generated on: Mon Mar 09 09:40:41 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "amplitude_selection.h"
#include "rand.h"
#include "amplitude_selection_data.h"

/* Variable Definitions */
static unsigned int state[625];

/* Function Declarations */
static double eml_rand_mt19937ar(unsigned int b_state[625]);

/* Function Definitions */
static double eml_rand_mt19937ar(unsigned int b_state[625])
{
  double r;
  int32_T exitg1;
  unsigned int u[2];
  int i;
  unsigned int b_r;
  int kk;
  unsigned int y;
  unsigned int b_y;
  unsigned int c_y;
  unsigned int d_y;
  boolean_T isvalid;
  boolean_T exitg2;

  /* ========================= COPYRIGHT NOTICE ============================ */
  /*  This is a uniform (0,1) pseudorandom number generator based on:        */
  /*                                                                         */
  /*  A C-program for MT19937, with initialization improved 2002/1/26.       */
  /*  Coded by Takuji Nishimura and Makoto Matsumoto.                        */
  /*                                                                         */
  /*  Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,      */
  /*  All rights reserved.                                                   */
  /*                                                                         */
  /*  Redistribution and use in source and binary forms, with or without     */
  /*  modification, are permitted provided that the following conditions     */
  /*  are met:                                                               */
  /*                                                                         */
  /*    1. Redistributions of source code must retain the above copyright    */
  /*       notice, this list of conditions and the following disclaimer.     */
  /*                                                                         */
  /*    2. Redistributions in binary form must reproduce the above copyright */
  /*       notice, this list of conditions and the following disclaimer      */
  /*       in the documentation and/or other materials provided with the     */
  /*       distribution.                                                     */
  /*                                                                         */
  /*    3. The names of its contributors may not be used to endorse or       */
  /*       promote products derived from this software without specific      */
  /*       prior written permission.                                         */
  /*                                                                         */
  /*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
  /*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
  /*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
  /*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT  */
  /*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
  /*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
  /*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
  /*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
  /*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
  /*  (INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE */
  /*  OF THIS  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  */
  /*                                                                         */
  /* =============================   END   ================================= */
  do {
    exitg1 = 0;
    for (i = 0; i < 2; i++) {
      u[i] = 0U;
    }

    for (i = 0; i < 2; i++) {
      b_r = b_state[624] + 1U;
      if (b_r >= 625U) {
        for (kk = 0; kk < 227; kk++) {
          y = (b_state[kk] & 2147483648U) | (b_state[1 + kk] & 2147483647U);
          if ((int)(y & 1U) == 0) {
            b_y = y >> 1U;
          } else {
            b_y = y >> 1U ^ 2567483615U;
          }

          b_state[kk] = b_state[397 + kk] ^ b_y;
        }

        for (kk = 0; kk < 396; kk++) {
          y = (b_state[kk + 227] & 2147483648U) | (b_state[228 + kk] &
            2147483647U);
          if ((int)(y & 1U) == 0) {
            c_y = y >> 1U;
          } else {
            c_y = y >> 1U ^ 2567483615U;
          }

          b_state[kk + 227] = b_state[kk] ^ c_y;
        }

        y = (b_state[623] & 2147483648U) | (b_state[0] & 2147483647U);
        if ((int)(y & 1U) == 0) {
          d_y = y >> 1U;
        } else {
          d_y = y >> 1U ^ 2567483615U;
        }

        b_state[623] = b_state[396] ^ d_y;
        b_r = 1U;
      }

      y = b_state[(int)b_r - 1];
      b_state[624] = b_r;
      y ^= y >> 11U;
      y ^= y << 7U & 2636928640U;
      y ^= y << 15U & 4022730752U;
      y ^= y >> 18U;
      u[i] = y;
    }

    r = 1.1102230246251565E-16 * ((double)(u[0] >> 5U) * 6.7108864E+7 + (double)
                                  (u[1] >> 6U));
    if (r == 0.0) {
      if ((b_state[624] >= 1U) && (b_state[624] < 625U)) {
        isvalid = TRUE;
      } else {
        isvalid = FALSE;
      }

      if (isvalid) {
        isvalid = FALSE;
        i = 1;
        exitg2 = FALSE;
        while ((exitg2 == FALSE) && (i < 625)) {
          if (b_state[i - 1] == 0U) {
            i++;
          } else {
            isvalid = TRUE;
            exitg2 = TRUE;
          }
        }
      }

      if (!isvalid) {
        b_r = 5489U;
        b_state[0] = 5489U;
        for (i = 0; i < 623; i++) {
          b_r = (b_r ^ b_r >> 30U) * 1812433253U + (1 + i);
          b_state[i + 1] = b_r;
        }

        b_state[624] = 624U;
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return r;
}

void b_rand(double r[22000])
{
  unsigned int b_r;
  int mti;
  if (!state_not_empty) {
    memset(&state[0], 0, 625U * sizeof(unsigned int));
    b_r = 5489U;
    state[0] = 5489U;
    for (mti = 0; mti < 623; mti++) {
      b_r = (b_r ^ b_r >> 30U) * 1812433253U + (1 + mti);
      state[mti + 1] = b_r;
    }

    state[624] = 624U;
    state_not_empty = TRUE;
  }

  for (mti = 0; mti < 22000; mti++) {
    r[mti] = eml_rand_mt19937ar(state);
  }
}

/* End of code generation (rand.c) */
