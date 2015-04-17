#include "Amplitude_selection.h"
#include "ISRs.h"


void mergeSort(float  x[], int  n);
void merge(float  x1[], int n1, float  x2[], int n2, float  tmp[]);


void amplitude_selection(){

	int  i,j;
	float  sum = 0;
	float  channel_mean[22];



	// used for calculating the mean of 22 channels
		for (j=0; j<16; ++j){
			sum = sum + fabs(Input0[j]);
		}
		channel_mean[0] = sum / 16;
		j = 0;
		sum = 0;



		for (j=0; j<16; ++j){
			sum = sum + fabs(Input1[j]);
		}
		channel_mean[1] = sum / 16;
		j = 0;
		sum = 0;



		for (j=0; j<16; ++j){
			sum = sum + fabs(Input2[j]);
		}
		channel_mean[2] = sum / 16;
		j = 0;
		sum = 0;



		for (j=0; j<16; ++j){
			sum = sum + fabs(Input3[j]);
		}
		channel_mean[3] = sum / 16;
		j = 0;
		sum = 0;



		for (j=0; j<16; ++j){
			sum = sum + fabs(Input4[j]);
		}
		channel_mean[4] = sum / 16;
		j = 0;
		sum = 0;



		for (j=0; j<16; ++j){
			sum = sum + fabs(Input5[j]);
		}
		channel_mean[5] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input6[j]);
		}
		channel_mean[6] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input7[j]);
		}
		channel_mean[7] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input8[j]);
		}
		channel_mean[8] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input9[j]);
		}
		channel_mean[9] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input10[j]);
		}
		channel_mean[10] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input11[j]);
		}
		channel_mean[11] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input12[j]);
		}
		channel_mean[12] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input13[j]);
		}
		channel_mean[13] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input14[j]);
		}
		channel_mean[14] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input15[j]);
		}
		channel_mean[15] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input16[j]);
		}
		channel_mean[16] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input17[j]);
		}
		channel_mean[17] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input18[j]);
		}
		channel_mean[18] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input19[j]);
		}
		channel_mean[19] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input20[j]);
		}
		channel_mean[20] = sum / 16;
		j = 0;
		sum = 0;


		for (j=0; j<16; ++j){
			sum = sum + fabs(Input21[j]);
		}
		channel_mean[21] = sum / 16;
		j = 0;



for(i = 0; i < 6; i++){
	result_channel[i] = -1;
}


	for(j = 0; j<6; j++){
		float largest = 0;
		int largestloc = 22;
		for(i = 21; i>=0 ; i--){
			if ((channel_mean[i] > largest) && (result_channel[0] != i) && (result_channel[1] != i) && (result_channel[2] != i) && (result_channel[3] != i) && (result_channel[4] != i) && (result_channel[5] != i)){
				largest = channel_mean[i];
				largestloc = i;
			}
		}
		result_mean[j] = largest;
		result_channel[j] = largestloc;

	}



}

