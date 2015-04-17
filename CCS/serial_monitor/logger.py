import sys
from serial import Serial
from serial.tools import list_ports

BAUD_RATE = 115200

if __name__ == '__main__':
	# automatically find Stellaris ICDI port
	icdi = list(list_ports.grep('ACM0'))
	log = open('log.txt', 'w')	

	if(not icdi):
		print('No ICDI port found! Please make sure' \
		      ' you plugged in the board!')
		sys.exit(1)
	
	port = Serial(icdi[0][0], BAUD_RATE, timeout=5)
	
	while True:
		sample = port.read()[0] << 4
		log.write('{} '.format(sample))
		

	port.close()
