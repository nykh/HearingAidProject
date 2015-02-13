

typedef unsigned short uint16_t;


void DAC_Init(uint16_t data);

  
//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: reply is returned
// send the 16-bit code to the SSI, return a reply

uint16_t DAC_Out2(uint16_t code);


//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
void DAC_Out(uint16_t code);
