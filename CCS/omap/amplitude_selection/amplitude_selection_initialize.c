/*
 * amplitude_selection_initialize.c
 *
 * Code generation for function 'amplitude_selection_initialize'
 *
 * C source code generated on: Mon Mar 09 09:40:40 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "amplitude_selection.h"
#include "amplitude_selection_initialize.h"
#include "eml_rand_mt19937ar_stateful.h"

/* Function Definitions */
void amplitude_selection_initialize(void)
{
  rt_InitInfAndNaN(8U);
  state_not_empty_init();
}

/* End of code generation (amplitude_selection_initialize.c) */
