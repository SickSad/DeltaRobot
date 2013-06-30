#!/usr/bin/env python

def main():
	min_delay = 400.0
	max_feedrate = 7800.0
	z_mm_step_size=  ((25.0 * 2.5) / (200.0 * 8.0))  #see kinematics.h
	print max_feedrate / (z_mm_step_size/min_delay)



if __name__ == "__main__":
	main()