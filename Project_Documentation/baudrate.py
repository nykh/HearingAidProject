# baudrate.py
# this script calculates the baud rate for TM4C123GXL board UART module

# The baud-rate divisor is a 22-bit number consisting of a 16-bit integer and a 6-bit fractional part.
# The number formed by these two values is used by the baud-rate generator to determine the bit
# period. 

# UART_IBRD_R is a 22 bit reg that represents the integer part
# UART_FBRD_R is the 6 bit fractional part
# formula:
# BRD = BRDI + BRDF = UARTSysClk / (ClkDiv * Baud Rate)

import math
import sys

def baudrate_divisor(Baudrate, SysClk, ClkDiv = 16):
    BRD = (SysClk * 1000) / (ClkDiv * Baudrate)
    f, i = math.modf(BRD)
    IBRD = math.floor(i)
    FBRD = math.floor(f * 64 + 0.5)
    return IBRD, FBRD
    
def print_usage():
    print("usage: ", __file__, 
        " <baud rage (in Hz) > < System Clock (in kHz) > [ -hse ]" )
        
if __name__ == "__main__":
    num_arg = len(sys.argv)-1
   
    if num_arg < 2 or num_arg > 3:
        print_usage()
        sys.exit(1)
    elif num_arg == 2:
        ibrd, fbrd = baudrate_divisor(int(sys.argv[1]), int(sys.argv[2]))
    elif num_arg == 3:
        if sys.argv[2] == '-hse':
            ibrd, fbrd = baudrate_divisor(int(sys.argv[1]), int(sys.argv[2]), 8)
        else:
            print_usage()
            sys.exit(1)
            
    print("_IBRD_R = {};".format(ibrd));
    print("_FBRD_R = {};".format(fbrd));
            
            
