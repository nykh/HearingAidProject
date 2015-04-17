/*
 * sortrows.c
 *
 * Code generation for function 'sortrows'
 *
 * C source code generated on: Mon Mar 09 09:40:41 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "amplitude_selection.h"
#include "sortrows.h"

/* Function Declarations */
static boolean_T eml_sort_le(const double v[44], int irow1, int irow2);

/* Function Definitions */
static boolean_T eml_sort_le(const double v[44], int irow1, int irow2)
{
  boolean_T p;
  boolean_T b0;
  p = TRUE;
  if ((v[irow1 - 1] == v[irow2 - 1]) || (rtIsNaN(v[irow1 - 1]) && rtIsNaN
       (v[irow2 - 1]))) {
    b0 = TRUE;
  } else {
    b0 = FALSE;
  }

  if (!b0) {
    if ((v[irow1 - 1] <= v[irow2 - 1]) || rtIsNaN(v[irow2 - 1])) {
      p = TRUE;
    } else {
      p = FALSE;
    }
  }

  return p;
}

void sortrows(double y[44])
{
  signed char idx[22];
  int k;
  signed char idx0[22];
  int i;
  int i2;
  int j;
  int pEnd;
  int p;
  int q;
  int qEnd;
  int kEnd;
  double ycol[22];
  for (k = 0; k < 22; k++) {
    idx[k] = (signed char)(k + 1);
  }

  for (k = 0; k < 22; k += 2) {
    if (eml_sort_le(y, k + 1, k + 2)) {
    } else {
      idx[k] = (signed char)(k + 2);
      idx[k + 1] = (signed char)(k + 1);
    }
  }

  for (i = 0; i < 22; i++) {
    idx0[i] = 1;
  }

  i = 2;
  while (i < 22) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < 23; pEnd = qEnd + i) {
      p = j;
      q = pEnd;
      qEnd = j + i2;
      if (qEnd > 23) {
        qEnd = 23;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if (eml_sort_le(y, idx[p - 1], idx[q - 1])) {
          idx0[k] = idx[p - 1];
          p++;
          if (p == pEnd) {
            while (q < qEnd) {
              k++;
              idx0[k] = idx[q - 1];
              q++;
            }
          }
        } else {
          idx0[k] = idx[q - 1];
          q++;
          if (q == qEnd) {
            while (p < pEnd) {
              k++;
              idx0[k] = idx[p - 1];
              p++;
            }
          }
        }

        k++;
      }

      for (k = 0; k + 1 <= kEnd; k++) {
        idx[(j + k) - 1] = idx0[k];
      }

      j = qEnd;
    }

    i = i2;
  }

  for (j = 0; j < 2; j++) {
    for (i = 0; i < 22; i++) {
      ycol[i] = y[(idx[i] + 22 * j) - 1];
    }

    memcpy(&y[22 * j], &ycol[0], 22U * sizeof(double));
  }
}

/* End of code generation (sortrows.c) */
