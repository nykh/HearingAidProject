import sys
from serial import Serial
from serial.tools import list_ports
import matplotlib.pyplot as plt
import time

BAUD_RATE = 115200



if __name__ == '__main__':
	# automatically find Stellaris ICDI port
	icdi = list(list_ports.grep('ACM0'))
	
	if(not icdi):
		print('No ICDI port found! Please make sure' \
		      ' you plugged in the board!')
		sys.exit(1)
	
	port = Serial(icdi[0][0], BAUD_RATE, timeout=5)
	
	# prepare real time plot
	plt.axis([0, 1000, 0, 4096])
	plt.ion()
	plt.show()
	x = 0
	
	while True:
		message = port.readline()

		# fro the component of frame see ../xbee/XBEE_Sampler_TM4C/main.c
		# current implementation the frame comes in three parts:
		# [ o0 | e0 ][ o1 | o2 ][ e1 | e2 ][ '\n' ]
			
		header = int(message[0])
		
		odd = ((header & 0x0F0) << 4) + int(message[1])
		even =  ((header << 8) + int(message[2])) & 0xFFF
		
		### for testing
		# print('odd number =  ', hex(odd), ' even number = ', hex(even))
		
		plt.scatter(x, odd)
		x += 1
		plt.scatter(x, even)
		x += 1
		plt.draw()
		### assuming we don't need this 
		# time.sleep(0.05)		
		
	port.close()
