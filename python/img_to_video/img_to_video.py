#!/usr/bin/env python
import subprocess
import os
import sys
from PIL import Image

def main():
	path = sys.argv[1]
	files = os.listdir(path)
	files = [os.path.join(path, f) for f in files if f.endswith('.JPG')]
	files.sort()

	f_index = 0

	for seconds in range(10):
		for f in files:
			filename = str(f_index).zfill(3) + '.png'
			img = Image.open(f)
			img = img.resize((1280,720), Image.ANTIALIAS)
			img.save(filename)
			#subprocess.call(["convert",filename,"-level","15%", filename])
			f_index += 1


	subprocess.call(['ffmpeg','-f','image2','-r','25', '-i', '%3d.png', '-vcodec','libx264', '-r','25', 'out.mp4'])



if __name__ == "__main__":
	main()