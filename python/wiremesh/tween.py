#!/usr/bin/env python
import math


def linear(time, begin, change, duration):
	time = float(time)
	begin = float(begin)
	change = float(change)
	duration = float(duration)
	val = ((change * time)/duration) + begin
	return val


def ease_in_quad(time, begin, change, duration):
	time = float(time)
	begin = float(begin)
	change = float(change)
	duration = float(duration)
	val = change*(time/duration)*(time/duration) + begin
	return val


def ease_out_quad(time, begin, change, duration):
	time = float(time)
	begin = float(begin)
	change = float(change)
	duration = float(duration)
	val = -change*(time/duration)*((time/duration)-2.0) + begin
	return val


def ease_in_out_quad(time, begin, change, duration):
	time = float(time)
	begin = float(begin)
	change = float(change)
	duration = float(duration)

	time = time/(duration/2.0)

	if time < 1.0:
		return change/2.0*time*time+begin
	return -change/2.0*((time-1)*(time-3) -1) + begin

def main():
	
	for time in range(20):
		print ease_out_quad(time, 0, 10, 20)


if __name__ == "__main__":
	main()