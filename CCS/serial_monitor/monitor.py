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
	plt.axis([0, 1000, 0, 256])
	plt.ion()
	plt.show()
	x = 0
	
	while True:
		sample = port.read()
		print(sample)
		sample = sample[0] << 4

		### for testing
		# print('odd number =  ', hex(odd), ' even number = ', hex(even))
		
		plt.scatter(x, sample)
		x += 1
		plt.draw()
		### assuming we don't need this 
		# time.sleep(0.05)		
		
	port.close()
