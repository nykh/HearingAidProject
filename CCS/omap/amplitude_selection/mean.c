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

/* Function Definitions */
double mean(const double x_data[22], const int x_size[1])
{
  double y;
  int k;
  if (x_size[0] == 0) {
    y = 0.0;
  } else {
    y = x_data[0];
    for (k = 2; k <= x_size[0]; k++) {
      y += x_data[k - 1];
    }
  }

  y /= (double)x_size[0];
  return y;
}

/* End of code generation (mean.c) */
