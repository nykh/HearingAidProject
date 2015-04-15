#include "sinusoid_lookup_table.h"
#include "ISRs.h"
#include "Decoder.h"





void decoder_init(void){
	int i;
	for (i = 0; i < 100; i++){
		outarray[i] = 0;
	}
	return;
}


void decode_channels(void){
	int i = 0;



for(i = 0; i<80; i++){

	outarray[i] = outarray[i+16]
			+ (result_mean[0] * sinusoid_lookup[result_channel[0]][i])
			+ (result_mean[1] * sinusoid_lookup[result_channel[1]][i])
			+ (result_mean[2] * sinusoid_lookup[result_channel[2]][i])
			+ (result_mean[3] * sinusoid_lookup[result_channel[3]][i])
			+ (result_mean[4] * sinusoid_lookup[result_channel[4]][i])
			+ (result_mean[5] * sinusoid_lookup[result_channel[5]][i]);



}

for(i = 0; i < 16; i++){
	thingout[i] = (outarray[i]);
}

return;
}
