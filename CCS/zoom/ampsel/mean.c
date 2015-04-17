/*
 * mean.c
 *
 * Code generation for function 'mean'
 *
 * C source code generated on: Mon Mar 09 09:40:41 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "amplitude_selection.h"
#include "mean.h"

typedef uint16_t integer

/* Function Definitions */
double mean(const integer x_data[22], uint16_t size)
{
  integer total = 0;
  uint16_t i;
  for(i = 0; i < size; ++i)
	  total += x_data[i];

  return total/size;
}

/* End of code generation (mean.c) */
