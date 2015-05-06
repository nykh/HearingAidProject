import sys
from serial import Serial
from serial.tools import list_ports
import pyqtgraph as pg
import time

BAUD_RATE = 115200

if __name__ == '__main__':
	# automatically find Stellaris ICDI port
	icdi = list(list_ports.grep('USB0'))
	
	if(not icdi):
		print('No ICDI port found! Please make sure' \
		      ' you plugged in the board!')
		sys.exit(1)
	
	port = Serial(icdi[0][0], BAUD_RATE, timeout=5)
	
	# prepare real time plot
	pw = pg.plot(title="Active Channels")
	pw.setXRange(0, 500)
	pw.setYRange(0, 22)
	s = pg.ScatterPlotItem()
	pw.addItem(s)
	pw.show()
	
	x = 0
	
	while True:
		group = [int(port.read()[0]) for i in range(6)]
		s.addPoints(x = x, y = group)
		pg.QtGui.QApplication.processEvents()
		x += 1
		
		if x == 500:
			x = 0
			s.clear()
		
	port.close()
