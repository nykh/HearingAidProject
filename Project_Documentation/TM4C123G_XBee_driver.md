# TM4C123G interface to XBee S1 module

## Related documentation
[Sparkfun XBee Manual](https://www.sparkfun.com/datasheets/Wireless/Zigbee/XBee-Manual.pdf)

## Physical connection

| XBee pin | MCon pin | color    |
|----------|----------|----------|
|  VCC (1) |  3.3 V   |          |
|  GND (10)|  GND     |          |
|  DIN (3) |  PB1 = U1Tx | Green  |
| DOUT (2) |  PB0 = U1Rx | Orange |

### Using resources on TM4C
- UART0 interfaces with PC serial port
- UART1 interfaces XBee
- Timer 1