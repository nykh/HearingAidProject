# TM4C123G basic talkthru

## Related documentation
[ADC Part of the TM4C123G Datasheet](http:/http://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf/)

[TLV5616C 12bit DAC chip](http://www.ti.com/lit/ds/symlink/tlv5616.pdf)

## Physical connection

| Mic Circuit| MCon pin | color     |
|------------|----------|-----------|
|    DOUT    |    PD3 (ADC0)   | Green     |

| DAC Circuit   |   MCon pin       | color |
|---------------|------------------|-------|
|   VDD (8)     |   3.3 V          |       |
|   AGND (5)    |   GND            |       |
|   CS  (3)     |   GND            |       |
|   DIN (1)     |  PB7 (SSITx)     |       |
|   SCLK (2)    |  PB4 (SSIClk)    |       |
|   FS (4)      |  PB5 (SCIFSS)    |       |

## Using resources on TM4C
- SSI2 interfaces with the DAC chip
	- PB4, 5, 7 multiplex
- ADC0 on PD3
- Timer 0A

