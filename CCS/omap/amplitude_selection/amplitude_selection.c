/*
 * amplitude_selection.c
 *
 * Code generation for function 'amplitude_selection'
 *
 * C source code generated on: Mon Mar 09 09:40:40 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "amplitude_selection.h"
#include "sortrows.h"
#include "mean.h"
#include "rand.h"
#include <stdio.h>

/* Function Definitions */
void amplitude_selection(double *result)
{
  double signal_original[22000];
  double inc;
  int i;
  int i0;
  int i1;
  int y_size_idx_0;
  int i2;
  int loop_ub;
  int i3;
  double y_data[484];
  double b_y_data[22];
  int y_size[1];
  double c_y_data[22];
  int b_y_size[1];
  double d_y_data[22];
  int c_y_size[1];
  double e_y_data[22];
  int d_y_size[1];
  double f_y_data[22];
  int e_y_size[1];
  double g_y_data[22];
  int f_y_size[1];
  double h_y_data[22];
  int g_y_size[1];
  double i_y_data[22];
  int h_y_size[1];
  double j_y_data[22];
  int i_y_size[1];
  double k_y_data[22];
  int j_y_size[1];
  double l_y_data[22];
  int k_y_size[1];
  double m_y_data[22];
  int l_y_size[1];
  double n_y_data[22];
  int m_y_size[1];
  double o_y_data[22];
  int n_y_size[1];
  double p_y_data[22];
  int o_y_size[1];
  double q_y_data[22];
  int p_y_size[1];
  double r_y_data[22];
  int q_y_size[1];
  double s_y_data[22];
  int r_y_size[1];
  double t_y_data[22];
  int s_y_size[1];
  double u_y_data[22];
  int t_y_size[1];
  double v_y_data[22];
  int u_y_size[1];
  double w_y_data[22];
  int v_y_size[1];
  double d0;
  double d1;
  double d2;
  double d3;
  double d4;
  double d5;
  double d6;
  double d7;
  double d8;
  double d9;
  double d10;
  double d11;
  double d12;
  double d13;
  double d14;
  double d15;
  double d16;
  double d17;
  double d18;
  double d19;
  double d20;
  double d21;
  double x[22];
  double dv0[44];
  double b[44];

  /*  This function gets the filtered signals */
  b_rand(signal_original);
  inc = 1.0;

  /*  variable for forwarding the z counter */
  memset(&result[0], 0, 132U * sizeof(double));

  /* arr = zeros(2,6); */
  for (i = 0; i < 22; i += 2) {
    if (i + 1 > i + 2) {
      i0 = 0;
      i1 = 0;
    } else {
      i0 = i;
      i1 = i + 2;
    }

    y_size_idx_0 = i1 - i0;
    for (i2 = 0; i2 < 22; i2++) {
      loop_ub = i1 - i0;
      for (i3 = 0; i3 < loop_ub; i3++) {
        y_data[i3 + y_size_idx_0 * i2] = signal_original[(i0 + i3) + 1000 * i2];
      }
    }

    loop_ub = i1 - i0;
    y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      b_y_data[i2] = y_data[i2];
    }

    loop_ub = i1 - i0;
    b_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      c_y_data[i2] = y_data[i2 + y_size_idx_0];
    }

    loop_ub = i1 - i0;
    c_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      d_y_data[i2] = y_data[i2 + (y_size_idx_0 << 1)];
    }

    loop_ub = i1 - i0;
    d_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      e_y_data[i2] = y_data[i2 + y_size_idx_0 * 3];
    }

    loop_ub = i1 - i0;
    e_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      f_y_data[i2] = y_data[i2 + (y_size_idx_0 << 2)];
    }

    loop_ub = i1 - i0;
    f_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      g_y_data[i2] = y_data[i2 + y_size_idx_0 * 5];
    }

    loop_ub = i1 - i0;
    g_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      h_y_data[i2] = y_data[i2 + y_size_idx_0 * 6];
    }

    loop_ub = i1 - i0;
    h_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      i_y_data[i2] = y_data[i2 + y_size_idx_0 * 7];
    }

    loop_ub = i1 - i0;
    i_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      j_y_data[i2] = y_data[i2 + (y_size_idx_0 << 3)];
    }

    loop_ub = i1 - i0;
    j_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      k_y_data[i2] = y_data[i2 + y_size_idx_0 * 9];
    }

    loop_ub = i1 - i0;
    k_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      l_y_data[i2] = y_data[i2 + y_size_idx_0 * 10];
    }

    loop_ub = i1 - i0;
    l_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      m_y_data[i2] = y_data[i2 + y_size_idx_0 * 11];
    }

    loop_ub = i1 - i0;
    m_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      n_y_data[i2] = y_data[i2 + y_size_idx_0 * 12];
    }

    loop_ub = i1 - i0;
    n_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      o_y_data[i2] = y_data[i2 + y_size_idx_0 * 13];
    }

    loop_ub = i1 - i0;
    o_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      p_y_data[i2] = y_data[i2 + y_size_idx_0 * 14];
    }

    loop_ub = i1 - i0;
    p_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      q_y_data[i2] = y_data[i2 + y_size_idx_0 * 15];
    }

    loop_ub = i1 - i0;
    q_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      r_y_data[i2] = y_data[i2 + (y_size_idx_0 << 4)];
    }

    loop_ub = i1 - i0;
    r_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      s_y_data[i2] = y_data[i2 + y_size_idx_0 * 17];
    }

    loop_ub = i1 - i0;
    s_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      t_y_data[i2] = y_data[i2 + y_size_idx_0 * 18];
    }

    loop_ub = i1 - i0;
    t_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      u_y_data[i2] = y_data[i2 + y_size_idx_0 * 19];
    }

    loop_ub = i1 - i0;
    u_y_size[0] = i1 - i0;
    for (i2 = 0; i2 < loop_ub; i2++) {
      v_y_data[i2] = y_data[i2 + y_size_idx_0 * 20];
    }

    loop_ub = i1 - i0;
    v_y_size[0] = i1 - i0;
    for (i0 = 0; i0 < loop_ub; i0++) {
      w_y_data[i0] = y_data[i0 + y_size_idx_0 * 21];
    }

    d0 = mean(b_y_data, y_size);
    d1 = mean(c_y_data, b_y_size);
    d2 = mean(d_y_data, c_y_size);
    d3 = mean(e_y_data, d_y_size);
    d4 = mean(f_y_data, e_y_size);
    d5 = mean(g_y_data, f_y_size);
    d6 = mean(h_y_data, g_y_size);
    d7 = mean(i_y_data, h_y_size);
    d8 = mean(j_y_data, i_y_size);
    d9 = mean(k_y_data, j_y_size);
    d10 = mean(l_y_data, k_y_size);
    d11 = mean(m_y_data, l_y_size);
    d12 = mean(n_y_data, m_y_size);
    d13 = mean(o_y_data, n_y_size);
    d14 = mean(p_y_data, o_y_size);
    d15 = mean(q_y_data, p_y_size);
    d16 = mean(r_y_data, q_y_size);
    d17 = mean(s_y_data, r_y_size);
    d18 = mean(t_y_data, s_y_size);
    d19 = mean(u_y_data, t_y_size);
    d20 = mean(v_y_data, u_y_size);
    d21 = mean(w_y_data, v_y_size);
    x[0] = d0;
    x[1] = d1;
    x[2] = d2;
    x[3] = d3;
    x[4] = d4;
    x[5] = d5;
    x[6] = d6;
    x[7] = d7;
    x[8] = d8;
    x[9] = d9;
    x[10] = d10;
    x[11] = d11;
    x[12] = d12;
    x[13] = d13;
    x[14] = d14;
    x[15] = d15;
    x[16] = d16;
    x[17] = d17;
    x[18] = d18;
    x[19] = d19;
    x[20] = d20;
    x[21] = d21;
    for (i0 = 0; i0 < 22; i0++) {
      dv0[i0] = x[i0];
      dv0[22 + i0] = 1.0 + (double)i0;
    }

    sortrows(dv0);
    for (i0 = 0; i0 < 22; i0++) {
      for (i1 = 0; i1 < 2; i1++) {
        b[i1 + (i0 << 1)] = dv0[i0 + 22 * i1];
      }
    }

    /*      counter = 22; */
    /*       for j = 1:(counter-6) */
    /*          [val, idx] = min(abs(x(1,:))); */
    /*           */
    /*          c(idx) = []; */
    /*          x(idx) = []; */
    /*          b(:,idx) = [];  */
    /*       end */
    /*      ss = [x ; c]; */
    for (i0 = 0; i0 < 6; i0++) {
      for (i1 = 0; i1 < 2; i1++) {
        result[i1 + (((int)(inc + (double)i0) - 1) << 1)] = b[i1 + ((16 + i0) <<
          1)];
      }
    }

    inc += 6.0;
  }
}

/* End of code generation (amplitude_selection.c) */
