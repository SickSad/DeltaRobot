#!/usr/bin/env python
import serial
import time
import datetime
import sys

def send_command(ser,cmd, log_file='log.txt'):
	
	if cmd.startswith('G1'):
		pass
	elif cmd.startswith('G92'):
		pass
	elif cmd.startswith('M3'):
		pass
	elif cmd.startswith('M4'):
		pass
	elif cmd.startswith('M5'):
		pass
	else:
		print "\tCommand not supported, skipping:"
		print '\t' + cmd
		with open(log_file, "a") as log:
		    log.write(cmd + '\n')
		return


	ser.write(cmd)
	line= ''
	while not line.startswith("ok"):
		line = ser.readline()
		print line[:-1]
		if line.startswith("rs"):
			line_number = int(line[3:])
			raise Exception("Error: need to resend line number "+ str(line_number) + '\n'+cmd)




def main():
	#gcode = "frame-vertex.gcode"
	#gcode = "cube.gcode"
	#gcode = "debug.gcode"
	gcode = sys.argv[1]

	ser = serial.Serial("/dev/ttyACM0", 9600, timeout=1)

	times = []

	f = open(gcode)
	commands = f.read()
	commands = commands.split('\n')

	for line_number, cmd in enumerate(commands):
		print str(line_number).zfill(6), str(len(commands)).zfill(6), cmd
		start_time = time.time()
		send_command(ser, cmd)
		cmd_time = time.time()-start_time
		times.append(cmd_time)
		avg_command_time = reduce(lambda x, y: x + y, times) / float(len(times))
		print '\taverage command_time:     ', avg_command_time
		predicted_time = (float(len(commands) - line_number)*avg_command_time)
		print '\tpredicted time remaining: ', str(datetime.timedelta(seconds=predicted_time))






if __name__ == "__main__":
	main()