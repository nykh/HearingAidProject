#ifndef __DAC_H__
#define __DAC_H__

void DAC_Init(uint16_t data);

//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
void DAC_Out(uint16_t code);

#endif //__DAC_H__
