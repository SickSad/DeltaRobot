#!/usr/bin/env python
import serial
import time

def caclulate_checksum(cmd):
	checksum = 0
	for c in cmd:
		checksum = checksum ^ ord(c)
	return checksum

def goto(ser, (x,y,z), extrude =0):
	cmd = "G1 X"+str(x)+" Y"+str(y)+" Z"+str(z) + " E"+str(extrude)
	checksum = caclulate_checksum(cmd)

	cmd += '*'+str(checksum)
	print cmd
	ser.write(cmd)
	line= ''
	while not line.startswith("ok"):
		line = ser.readline()
		print line[:-1]
		if line.startswith("rs"):
			line_number = int(line[3:])
			raise Exception("Error: need to resend line number "+ str(line_number) + '\n'+cmd)


def main():
	ser = serial.Serial("/dev/ttyACM0", 9600, timeout=1)
	z = -10
	x = 50
	y = 50
	goto(ser, (0,0,z), 0)
	goto(ser, (x,y,z), 0)
	goto(ser, (-x,y,z), 0)
	goto(ser, (-x,-y,z), 0)
	goto(ser, (x,-y,z), 0)
	goto(ser, (x,y,z), 0)
	goto(ser, (0,0,z), 0)
	goto(ser, (0,0,0), 0)


	return







	print "done!"
	
	#while True:
	#	print ser.readline()




if __name__ == "__main__":
	main()