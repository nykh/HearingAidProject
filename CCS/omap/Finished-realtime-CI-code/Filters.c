#include "Filters.h"

void filter(float  input);


void biquad1(int  i);
void biquad2(int  i);
void biquad3(int  i);
void biquad4(int  i);
void biquad5(int  i);
void biquad6(int  i);
void biquad7(int  i);
void biquad8(int  i);
void biquad9(int  i);
void biquad10(int  i);
void biquad11(int  i);
void biquad12(int  i);
void biquad13(int  i);
void biquad14(int  i);
void biquad15(int  i);
void biquad16(int  i);
void biquad17(int  i);
void biquad18(int  i);
void biquad19(int  i);
void biquad20(int  i);
void biquad21(int  i);
void biquad22(int  i);


#define N 2
#define M1 2			     // Number of BIQUADS in this filter (1/2 the order)
float  B1[M1][N + 1] = { { 1, -0.67302695319845629, 1 }, { 1, -1.9999732532795402,   1 } };  // numerator coefficients
float  A1[M1][N + 1] = { { 1, -1.9833007338450102,  0.99170268904796721 }, { 1, -1.9865904115077992,  0.9928399834701005 } };  // denominator coefficients
float  G1[M1 + 1] = { 0.012163232189171308, 0.012163232189171308, 1 };               // scale factors
float  X1[M1][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y1[M1][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput1 = 0.0;

#define M2 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B2[M2][N + 1] = { { 1,  -0.38554400615391082,  1  }, { 1, -1.9999620566631022,   1 } };  // numerator coefficients
float  A2[M2][N + 1] = { { 1,  -1.978684635578426,   0.99033408868486295 }, { 1,  -1.9829507894221492,  0.99164417450768072 }};  // denominator coefficients
float  G2[M2 + 1] = { 0.012857790961013133, 0.012857790961013133 , 1 };               // scale factors
float  X2[M2][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y2[M2][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput2 = 0.0;

#define M3 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B3[M3][N + 1] = { { 1,   0.038091261266285759,  1 }, { 1, -1.9999516020492689, 1 } };  // numerator coefficients
float  A3[M3][N + 1] = { { 1, -1.9716332017088345,  0.98800990055885229 }, { 1, - 1.9776447354770679,  0.98970194740484352 }};  // denominator coefficients
float  G3[M3 + 1] = { 0.014148530284949747, 0.014148530284949747, 1 };               // scale factors
float  x3[M3][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  y3[M3][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput3 = 0.0;

#define M4 2			     // Number of BIQUADS in this filter (1/2 the order)
float  B4[M4][N + 1] = { { 1,   0.32462946581116714,  1 }, { 1, -1.9999285498909831,   1 }};  // numerator coefficients
float  A4[M4][N + 1] = { { 1, -1.9633548274363053,  0.98620510324958033 }, { 1, -1.9711388811878319,  0.98810031372625728 } };  // denominator coefficients
float  G4[M4 + 1] = { 0.015275613833317533, 0.015275613833317533, 1 };               // scale factors
float  x4[M4][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  y4[M4][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput4 = 0.0;

#define M5 2 				     // Number of BIQUADS in this filter (1/2 the order)
float  B5[M5][N + 1] = { { 1,   0.66917530390137059,  1 }, { 1, -1.9999028566360106,   1 } };  // numerator coefficients
float  A5[M5][N + 1] = { { 1, -1.951467027426145,   0.98345645145102567 }, { 1, -1.9620964298237282,  0.98575073211779307 }};  // denominator coefficients
float  G5[M5 + 1] = { 0.017082961548756791, 0.017082961548756791, 1 };               // scale factors
float  x5[M5][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  y5[M5][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput5 = 0.0;

#define M6 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B6[M6][N + 1] = { { 1, 0.93213169012758545,  1 }, { 1, -1.9998603980224026,   1 }};  // numerator coefficients
float  A6[M6][N + 1] = { { 1, -1.9361682679718828,  0.98074992253259363 }, { 1, -1.9502522937737234,  0.98337255603671325 }};  // denominator coefficients
float  G6[M6 + 1] = { 0.018992732591604174, 0.018992732591604174, 1 };               // scale factors
float  x6[M6][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  y6[M6][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput6 = 0.0;

#define M7 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B7[M7][N + 1] = { { 1,   1.1872528189854266,  1 }, { 1, -1.9998078854126993,  1 }};  // numerator coefficients
float  A7[M7][N + 1] = { { 1, -1.9149313166766961,  0.97712414438037309 }, { 1, -1.9340998087770285,  0.9802400111367966}};  // denominator coefficients
float  G7[M7 + 1] = { 0.021648184022452881, 0.021648184022452881, 1 };               // scale factors
float  x7[M7][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  y7[M7][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput7 = 0.0;

#define M8 	2			     // Number of BIQUADS in this filter (1/2 the order)
float  B8[M8][N + 1] = { { 1,   1.3865816109647258,  1 }, { 1 -1.9997308323307195,  1 }};  // numerator coefficients
float  A8[M8][N + 1] = { { 1, -1.8864490161042289,  0.97308186004223751 }, { 1, -1.9123369247502031,  0.97670815485022677 }};  // denominator coefficients
float  G8[M8 + 1] = { 0.024734034942879055, 0.024734034942879055, 1 };               // scale factors
float  x8[M8][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  y8[M8][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput8 = 0.0;

#define M9 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B9[M9][N + 1] = { { 1,   1.5501380947429517,  1 }, { 1, -1.9996274057890013,  1 }};  // numerator coefficients
float  A9[M9][N + 1] = { { 1, -1.847533733294684,   0.96816263985347606 }, { 1, -1.8827622163002853,  0.97241195279584258 }};  // denominator coefficients
float  G9[M9 + 1] = { 0.028592987173501269, 0.028592987173501269, 1 };               // scale factors
float  x9[M9][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  y9[M9][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput9 = 0.0;

#define M10 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B10[M10][N + 1] = { { 1,   1.6684958195845208,  1 }, { 1, -1.9994731868731361,  1 }};  // numerator coefficients
float  A10[M10][N + 1] = { { 1, -1.7956125894210877,  0.96287026828617295 }, { 1, -1.8428871790752379,  0.96770357409374763 }};  // denominator coefficients
float  G10[M10 + 1] = { 0.03286673340268325, 0.03286673340268325, 1 };               // scale factors
float  X10[M10][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y10[M10][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput10 = 0.0;

#define M11 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B11[M11][N + 1] = { { 1,   1.7686481099850764,  1 }, { 1, -1.999285857083783,   1 }};  // numerator coefficients
float  A11[M11][N + 1] = { { 1, -1.7237666810938892,  0.95582571421445628 }, { 1, -1.788537176162003,   0.96149969178199834 }};  // denominator coefficients
float  G11[M11 + 1] = { 0.038618008651387085, 0.038618008651387085, 1 };               // scale factors
float  X11[M11][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y11[M11][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput11 = 0.0;

#define M12 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B12[M12][N + 1] = { { 1,   1.8361395331731591,  1 }, { 1, -1.9989991521249788,  1 }};  // numerator coefficients
float  A12[M12][N + 1] = { { 1, -1.6280543126711762,  0.94850028667753039 }, { 1, -1.7148725150135899,  0.95485575615276064 }};  // denominator coefficients
float  G12[M12 + 1] = { 0.044754492174691483, 0.044754492174691483, 1 };               // scale factors
float  X12[M12][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y12[M12][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput12 = 0.0;

#define M13 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B13[M13][N + 1] = { { 1, 1.8897602915210525,  1 }, { 1, -1.9986465327270904,  1 }};  // numerator coefficients
float  A13[M13][N + 1] = { { 1, -1.4975832174211476,  0.93911527811793105 }, { 1, -1.6152424707683948,  0.94632804769870371 }};  // denominator coefficients
float  G13[M13 + 1] = { 0.052694580859073137, 0.052694580859073137, 1 };               // scale factors
float  X13[M13][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y13[M13][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput13 = 0.0;

#define M14 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B14[M14][N + 1] = { { 1,   1.9260282433155325,  1 }, { 1, -1.998133521650415,   1 }  };  // numerator coefficients
float  A14[M14][N + 1] = { { 1, -1.3248614080560379,  0.92917130151809679 }, { 1, -1.4809355645523401,  0.93694307761352946 } };  // denominator coefficients
float  G14[M14 + 1] = { 0.061323602960183535, 0.061323602960183535, 1 };               // scale factors
float  X14[M14][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y14[M14][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput14 = 0.0;

#define M15 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B15[M15][N + 1] = { { 1,   1.953128800082802,   1 }, { 1, -1.9975039095045404,  1 }};  // numerator coefficients
float  A15[M15][N + 1] = { { 1, -1.0954292441902762,  0.91704411924574503 }, { 1, -1.3020638667234397,  0.92522273420228973 }};  // denominator coefficients
float  G15[M15 + 1] = { 0.072033230268895049, 0.072033230268895049, 1 };               // scale factors
float  X15[M15][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y15[M15][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput15 = 0.0;

#define M16 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B16[M16][N + 1] = { { 1,   1.9717588703192113,  1 }, { 1, -1.9966922599246524,  1 }};  // numerator coefficients
float  A16[M16][N + 1] = { { 1, -0.79716563004621444,  0.90348736302075794 }, { 1, -1.0655537896201075,   0.91139864357584366 }};  // denominator coefficients
float  G16[M16 + 1] = { 0.084397377734703474, 0.084397377734703474, 1 };               // scale factors
float  X16[M16][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y16[M16][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput16 = 0.0;

#define M17 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B17[M17][N + 1] = { { 1,   1.9842596563276937,  1 }, { 1, -1.9956994740947827,  1} };  // numerator coefficients
float  A17[M17][N + 1] = { { 1, -0.41940302046589301,  0.88852683475178729 }, { 1, -0.75905032811788653,  0.89489229552035732 }};  // denominator coefficients
float  G17[M17 + 1] = { 0.0986855472753915, 0.0986855472753915, 1 };               // scale factors
float  X17[M17][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y17[M17][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput17 = 0.0;

#define M18 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B18[M18][N + 1] = { { 1,   1.9884912895963558,  1 }, { 1, -1.9910980581509772,  1 }};  // numerator coefficients
float  A18[M18][N + 1] = { { 1,   0.047515105172799887,  0.89647820046898252 }, { 1, -0.28957779574450387,   0.89759811928883726 }};  // denominator coefficients
float  G18[M18 + 1] = { 0.093831022466115591, 0.093831022466115591, 1 };               // scale factors
float  X18[M18][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y18[M18][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput18 = 0.0;

#define M19 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B19[M19][N + 1] = { { 1, -1.9934847285532764,  1 }, {1,   1.9968870073974991,  1 }};  // numerator coefficients
float  A19[M19][N + 1] = { { 1,  0.093266317177035263,  0.84925402621815316 }, { 1,  0.57312911199084493,   0.85592165628907901 }};  // denominator coefficients
float  G19[M19 + 1] = { 0.13460893590478262, 0.13460893590478262, 1 };               // scale factors
float  X19[M19][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y19[M19][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput19 = 0.0;

#define M20 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B20[M20][N + 1] = { { 1, -1.9926895069360426,  1 }, { 1,   1.9991349131342053,  1 }};  // numerator coefficients
float  A20[M20][N + 1] = { { 1,  1.1294456007062506,   0.84208508030830387 }, { 1,  0.61687404310858562,  0.81479051805350955 }};  // denominator coefficients
float  G20[M20 + 1] = { 0.15721195907386637, 0.15721195907386637, 1 };               // scale factors
float  X20[M20][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y20[M20][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput20 = 0.0;

#define M21 2				     // Number of BIQUADS in this filter (1/2 the order)
float  B21[M21][N + 1] = { { 1, -1.9924953463627537,  1 }, { 1,   1.9998937438149567,  1 }};  // numerator coefficients
float  A21[M21][N + 1] = { { 1,  1.1317427553626487,  0.76115662753482249 }, { 1,  1.6188743759396704,  0.8437940555481831 }};  // denominator coefficients
float  G21[M21 + 1] = { 0.18267645050055339, 0.18267645050055339, 1 };               // scale factors
float  X21[M21][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y21[M21][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput21 = 0.0;

#define M22 2			     // Number of BIQUADS in this filter (1/2 the order)
float  B22[M22][N + 1] = { { 1, -1.5217678061199682,   1 }, { 1, -0.25262268219163814,  1 }};  // numerator coefficients
float  A22[M22][N + 1] = { { 1,  1.6568943478973628,  0.71623235721733935 }, { 1,  1.6659820080169738,  0.88074061420728622 }};  // denominator coefficients
float  G22[M22 + 1] = { 0.2952673585743677, 0.0048486288169763744, 1};               // scale factors
float  X22[M22][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // input value (buffered)
float  Y22[M22][N+1] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};   // output values (buffered)
float  filteroutput22 = 0.0;

	

void filter(float  input){
		int i = 0;
X1[0][0] = input*G1[0];					// current input value
X2[0][0] = input*G2[0];					// current input value
x3[0][0] = input*G3[0];					// current input value
x4[0][0] = input*G4[0];					// current input value
x5[0][0] = input*G5[0];					// current input value
x6[0][0] = input*G6[0];					// current input value
x7[0][0] = input*G7[0];					// current input value
x8[0][0] = input*G8[0];					// current input value
x9[0][0] = input*G9[0];					// current input value
X10[0][0] = input*G10[0];					// current input value
X11[0][0] = input*G11[0];					// current input value
X12[0][0] = input*G12[0];					// current input value
X13[0][0] = input*G13[0];					// current input value
X14[0][0] = input*G14[0];					// current input value
X15[0][0] = input*G15[0];					// current input value
X16[0][0] = input*G16[0];					// current input value
X17[0][0] = input*G17[0];					// current input value
X18[0][0] = input*G18[0];					// current input value
X19[0][0] = input*G19[0];					// current input value
X20[0][0] = input*G20[0];					// current input value
X21[0][0] = input*G21[0];					// current input value
X22[0][0] = input*G22[0];					// current input value


for (i=0;i<M1;i++){
	biquad1(i);                               // implement the i_th biquad in the nth filter
}
for (i=0;i<M2;i++){
	biquad2(i);                               
}
for (i=0;i<M3;i++){
	biquad3(i);                               
}
for (i=0;i<M4;i++){
	biquad4(i);                               
}
for (i=0;i<M5;i++){
	biquad5(i);                               
}
for (i=0;i<M6;i++){
	biquad6(i);                               
}
for (i=0;i<M7;i++){
	biquad7(i);                               
}
for (i=0;i<M8;i++){
	biquad8(i);                               
}
for (i=0;i<M9;i++){
	biquad9(i);                               
}
for (i=0;i<M10;i++){
	biquad10(i);                               
}
for (i=0;i<M11;i++){
	biquad11(i);                               
}
for (i=0;i<M12;i++){
	biquad12(i);                               
}
for (i=0;i<M13;i++){
	biquad13(i);                               
}
for (i=0;i<M14;i++){
	biquad14(i);                               
}
for (i=0;i<M15;i++){
	biquad15(i);                               
}
for (i=0;i<M16;i++){
	biquad16(i);                               
}
for (i=0;i<M17;i++){
	biquad17(i);                               
}
for (i=0;i<M18;i++){
	biquad18(i);                               
}
for (i=0;i<M19;i++){
	biquad19(i);                               
}
for (i=0;i<M20;i++){
	biquad20(i);                               
}
for (i=0;i<M21;i++){
	biquad21(i);                               
}
for (i=0;i<M22;i++){
	biquad22(i);                               
}

return;

}






void biquad1(int  i){

Y1[i][0] = (-A1[i][1] *Y1[i][1]) + (-A1[i][2]* Y1[i][2]) + (B1[i][0]* X1[i][0]) + (B1[i][1]* X1[i][1]) + (B1[i][2]* X1[i][2]);

X1[i][2] = X1[i][1];
X1[i][1] = X1[i][0];
Y1[i][2] = Y1[i][1];
Y1[i][1] = Y1[i][0];

if(i == M1-1){
	filteroutput1 = Y1[i][0]*G1[i+1];	
}
else{
	X1[i+1][0] = Y1[i][0]*G1[i+1];
	}
return;
}


void biquad2(int  i){

Y2[i][0] = (-A2[i][1] *Y2[i][1]) + (-A2[i][2]* Y2[i][2]) + (B2[i][0]* X2[i][0]) + (B2[i][1]* X2[i][1]) + (B2[i][2]* X2[i][2]);

X2[i][2] = X2[i][1];
X2[i][1] = X2[i][0];
Y2[i][2] = Y2[i][1];
Y2[i][1] = Y2[i][0];

if(i == M2-1){
	filteroutput2 = Y2[i][0]*G2[i+1];	
}
else{
	X2[i+1][0] = Y2[i][0]*G2[i+1];
	}
return;
}


void biquad3(int  i){

y3[i][0] = (-A3[i][1]* y3[i][1]) + (-A3[i][2]* y3[i][2]) + (B3[i][0]* x3[i][0]) + (B3[i][1]* x3[i][1]) + (B3[i][2]* x3[i][2]);

x3[i][2] = x3[i][1];
x3[i][1] = x3[i][0];
y3[i][2] = y3[i][1];
y3[i][1] = y3[i][0];

if(i == M3-1){
	filteroutput3 = y3[i][0]*G3[i+1];	
}
else{
	x3[i+1][0] = y3[i][0]*G3[i+1];
	}
return;
}


void biquad4(int  i){

y4[i][0] = (-A4[i][1]* y4[i][1]) + (-A4[i][2]* y4[i][2]) + (B4[i][0]* x4[i][0]) + (B4[i][1]* x4[i][1]) + (B4[i][2]* x4[i][2]);

x4[i][2] = x4[i][1];
x4[i][1] = x4[i][0];
y4[i][2] = y4[i][1];
y4[i][1] = y4[i][0];

if(i == M4-1){
	filteroutput4 = y4[i][0]*G4[i+1];	
}
else{
	x4[i+1][0] = y4[i][0]*G4[i+1];
	}
return;
}

void biquad5(int  i){

y5[i][0] = (-A5[i][1]* y5[i][1]) + (-A5[i][2]* y5[i][2]) + (B5[i][0]* x5[i][0]) + (B5[i][1]* x5[i][1]) + (B5[i][2]* x5[i][2]);

x5[i][2] = x5[i][1];
x5[i][1] = x5[i][0];
y5[i][2] = y5[i][1];
y5[i][1] = y5[i][0];

if(i == M5-1){
	filteroutput5 = y5[i][0]*G5[i+1];	
}
else{
	x5[i+1][0] = y5[i][0]*G5[i+1];
	}
return;
}


void biquad6(int  i){

y6[i][0] = (-A6[i][1]* y6[i][1]) + (-A6[i][2]* y6[i][2]) + (B6[i][0]* x6[i][0]) + (B6[i][1]* x6[i][1]) + (B6[i][2]* x6[i][2]);

x6[i][2] = x6[i][1];
x6[i][1] = x6[i][0];
y6[i][2] = y6[i][1];
y6[i][1] = y6[i][0];

if(i == M6-1){
	filteroutput6 = y6[i][0]*G6[i+1];	
}
else{
	x6[i+1][0] = y6[i][0]*G6[i+1];
	}
return;
}

void biquad7(int  i){

y7[i][0] = (-A7[i][1]* y7[i][1]) + (-A7[i][2]* y7[i][2]) + (B7[i][0]* x7[i][0]) + (B7[i][1]* x7[i][1]) + (B7[i][2]* x7[i][2]);

x7[i][2] = x7[i][1];
x7[i][1] = x7[i][0];
y7[i][2] = y7[i][1];
y7[i][1] = y7[i][0];

if(i == M7-1){
	filteroutput7 = y7[i][0]*G7[i+1];	
}
else{
	x7[i+1][0] = y7[i][0]*G7[i+1];
	}
return;
}


void biquad8(int  i){

y8[i][0] = (-A8[i][1]* y8[i][1]) + (-A8[i][2]* y8[i][2]) + (B8[i][0]* x8[i][0]) + (B8[i][1]* x8[i][1]) + (B8[i][2]* x8[i][2]);

x8[i][2] = x8[i][1];
x8[i][1] = x8[i][0];
y8[i][2] = y8[i][1];
y8[i][1] = y8[i][0];

if(i == M8-1){
	filteroutput8 = y8[i][0]*G8[i+1];	
}
else{
	x8[i+1][0] = y8[i][0]*G8[i+1];
	}
return;
}

void biquad9(int  i){

y9[i][0] = (-A9[i][1]* y9[i][1]) + (-A9[i][2]* y9[i][2]) + (B9[i][0]* x9[i][0]) + (B9[i][1]* x9[i][1]) + (B9[i][2]* x9[i][2]);

x9[i][2] = x9[i][1];
x9[i][1] = x9[i][0];
y9[i][2] = y9[i][1];
y9[i][1] = y9[i][0];

if(i == M9-1){
	filteroutput9 = y9[i][0]*G9[i+1];	
}
else{
	x9[i+1][0] = y9[i][0]*G9[i+1];
	}
return;
}


void biquad10(int  i){

Y10[i][0] = (-A10[i][1]* Y10[i][1]) + (-A10[i][2]* Y10[i][2]) + (B10[i][0]* X10[i][0]) + (B10[i][1]* X10[i][1]) + (B10[i][2]* X10[i][2]);

X10[i][2] = X10[i][1];
X10[i][1] = X10[i][0];
Y10[i][2] = Y10[i][1];
Y10[i][1] = Y10[i][0];

if(i == M10-1){
	filteroutput10 = Y10[i][0]*G10[i+1];	
}
else{
	X10[i+1][0] = Y10[i][0]*G10[i+1];
	}
return;
}

void biquad11(int  i){

Y11[i][0] = (-A11[i][1]* Y11[i][1]) + (-A11[i][2]* Y11[i][2]) + (B11[i][0]* X11[i][0]) + (B11[i][1]* X11[i][1]) + (B11[i][2]* X11[i][2]);

X11[i][2] = X11[i][1];
X11[i][1] = X11[i][0];
Y11[i][2] = Y11[i][1];
Y11[i][1] = Y11[i][0];

if(i == M11-1){
	filteroutput11 = Y11[i][0]*G11[i+1];	
}
else{
	X11[i+1][0] = Y11[i][0]*G11[i+1];
	}
return;
}


void biquad12(int  i){

Y12[i][0] = (-A12[i][1]* Y12[i][1]) + (-A12[i][2]* Y12[i][2]) + (B12[i][0]* X12[i][0]) + (B12[i][1]* X12[i][1]) + (B12[i][2]* X12[i][2]);

X12[i][2] = X12[i][1];
X12[i][1] = X12[i][0];
Y12[i][2] = Y12[i][1];
Y12[i][1] = Y12[i][0];

if(i == M12-1){
	filteroutput12 = Y12[i][0]*G12[i+1];	
}
else{
	X12[i+1][0] = Y12[i][0]*G12[i+1];
	}
return;
}

void biquad13(int  i){

Y13[i][0] = (-A13[i][1]* Y13[i][1]) + (-A13[i][2]* Y13[i][2]) + (B13[i][0]* X13[i][0]) + (B13[i][1]* X13[i][1]) + (B13[i][2]* X13[i][2]);

X13[i][2] = X13[i][1];
X13[i][1] = X13[i][0];
Y13[i][2] = Y13[i][1];
Y13[i][1] = Y13[i][0];

if(i == M13-1){
	filteroutput13 = Y13[i][0]*G13[i+1];	
}
else{
	X13[i+1][0] = Y13[i][0]*G13[i+1];
	}
return;
}


void biquad14(int  i){

Y14[i][0] = (-A14[i][1]* Y14[i][1]) + (-A14[i][2]* Y14[i][2]) + (B14[i][0]* X14[i][0]) + (B14[i][1]* X14[i][1]) + (B14[i][2]* X14[i][2]);

X14[i][2] = X14[i][1];
X14[i][1] = X14[i][0];
Y14[i][2] = Y14[i][1];
Y14[i][1] = Y14[i][0];

if(i == M14-1){
	filteroutput14 = Y14[i][0]*G14[i+1];	
}
else{
	X14[i+1][0] = Y14[i][0]*G14[i+1];
	}
return;
}

void biquad15(int  i){

Y15[i][0] = (-A15[i][1]* Y15[i][1]) + (-A15[i][2]* Y15[i][2]) + (B15[i][0]* X15[i][0]) + (B15[i][1]* X15[i][1]) + (B15[i][2]* X15[i][2]);

X15[i][2] = X15[i][1];
X15[i][1] = X15[i][0];
Y15[i][2] = Y15[i][1];
Y15[i][1] = Y15[i][0];

if(i == M15-1){
	filteroutput15 = Y15[i][0]*G15[i+1];	
}
else{
	X15[i+1][0] = Y15[i][0]*G15[i+1];
	}
return;
}


void biquad16(int  i){

Y16[i][0] = (-A16[i][1]* Y16[i][1]) + (-A16[i][2]* Y16[i][2]) + (B16[i][0]* X16[i][0]) + (B16[i][1]* X16[i][1]) + (B16[i][2]* X16[i][2]);

X16[i][2] = X16[i][1];
X16[i][1] = X16[i][0];
Y16[i][2] = Y16[i][1];
Y16[i][1] = Y16[i][0];

if(i == M16-1){
	filteroutput16 = Y16[i][0]*G16[i+1];	
}
else{
	X16[i+1][0] = Y16[i][0]*G16[i+1];
	}
return;
}

void biquad17(int  i){

Y17[i][0] = (-A17[i][1]* Y17[i][1]) + (-A17[i][2]* Y17[i][2]) + (B17[i][0]* X17[i][0]) + (B17[i][1]* X17[i][1]) + (B17[i][2]* X17[i][2]);

X17[i][2] = X17[i][1];
X17[i][1] = X17[i][0];
Y17[i][2] = Y17[i][1];
Y17[i][1] = Y17[i][0];

if(i == M17-1){
	filteroutput17 = Y17[i][0]*G17[i+1];	
}
else{
	X17[i+1][0] = Y17[i][0]*G17[i+1];
	}
return;
}


void biquad18(int  i){

Y18[i][0] = (-A18[i][1]* Y18[i][1]) + (-A18[i][2]* Y18[i][2]) + (B18[i][0]* X18[i][0]) + (B18[i][1]* X18[i][1]) + (B18[i][2]* X18[i][2]);

X18[i][2] = X18[i][1];
X18[i][1] = X18[i][0];
Y18[i][2] = Y18[i][1];
Y18[i][1] = Y18[i][0];

if(i == M18-1){
	filteroutput18 = Y18[i][0]*G18[i+1];	
}
else{
	X18[i+1][0] = Y18[i][0]*G18[i+1];
	}
return;
}

void biquad19(int  i){

Y19[i][0] = (-A19[i][1]* Y19[i][1]) + (-A19[i][2]* Y19[i][2]) + (B19[i][0]* X19[i][0]) + (B19[i][1]* X19[i][1]) + (B19[i][2]* X19[i][2]);

X19[i][2] = X19[i][1];
X19[i][1] = X19[i][0];
Y19[i][2] = Y19[i][1];
Y19[i][1] = Y19[i][0];

if(i == M19-1){
	filteroutput19 = Y19[i][0]*G19[i+1];	
}
else{
	X19[i+1][0] = Y19[i][0]*G19[i+1];
	}
return;
}


void biquad20(int  i){

Y20[i][0] = (-A20[i][1]* Y20[i][1]) + (-A20[i][2]* Y20[i][2]) + (B20[i][0]* X20[i][0]) + (B20[i][1]* X20[i][1]) + (B20[i][2]* X20[i][2]);

X20[i][2] = X20[i][1];
X20[i][1] = X20[i][0];
Y20[i][2] = Y20[i][1];
Y20[i][1] = Y20[i][0];

if(i == M20-1){
	filteroutput20 = Y20[i][0]*G20[i+1];	
}
else{
	X20[i+1][0] = Y20[i][0]*G20[i+1];
	}
return;
}
void biquad21(int  i){

Y21[i][0] = (-A21[i][1]* Y21[i][1]) + (-A21[i][2]* Y21[i][2]) + (B21[i][0]* X21[i][0]) + (B21[i][1]* X21[i][1]) + (B21[i][2]* X21[i][2]);

X21[i][2] = X21[i][1];
X21[i][1] = X21[i][0];
Y21[i][2] = Y21[i][1];
Y21[i][1] = Y21[i][0];

if(i == M21-1){
	filteroutput21 = Y21[i][0]*G21[i+1];	
}
else{
	X21[i+1][0] = Y21[i][0]*G21[i+1];
	}
return;
}


void biquad22(int  i){

Y22[i][0] = (-A22[i][1]* Y22[i][1]) + (-A22[i][2]* Y22[i][2]) + (B22[i][0]* X22[i][0]) + (B22[i][1]* X22[i][1]) + (B22[i][2]* X22[i][2]);

X22[i][2] = X22[i][1];
X22[i][1] = X22[i][0];
Y22[i][2] = Y22[i][1];
Y22[i][1] = Y22[i][0];

if(i == M22-1){
	filteroutput22 = Y22[i][0]*G22[i+1];	
}
else{
	X22[i+1][0] = Y22[i][0]*G22[i+1];
	}
return;
}
