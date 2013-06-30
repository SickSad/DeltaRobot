#!/usr/bin/env python


#!/usr/bin/env python

import math
import random
import model_manipulation
import model_to_gcode
import sys
import os


def circle(raidus=10.0, degree_steps=20, position=(0,0,0)):
    points = model_manipulation.generate_circle(raidus, degree_steps)
    points = model_manipulation.add_offset(points, position)
    face = range(len(points))
    face.append(0)
    return points, face

def line(start=(0,0,50),end = (0,0,10)):
    points = [start, end]
    face = range(len(points))
    return points, face

def append_shapes((points,faces),(new_points,new_face)):
    if new_points == None or new_face == None:
        return points, faces
    new_face = [v +len(points) for v in new_face]
    faces.append(new_face)
    points += (new_points)
    return points, faces

def create_filename(f_index, direc='animation/'):
    f_index = str(f_index).zfill(3)+'.gcode'
    return os.path.join(direc, f_index)

class ExpandingCircle:
    def __init__(self, position=(0,0,0), max_radius = 20, start_tick = 0, duration = 10):
        self.size = 0
        self.max_radius = max_radius
        self.position = position
        self.duration = duration
        self.start_tick = start_tick
        self.current_tick = 0

    def get(self, tick):
        if tick < self.start_tick or tick > self.start_tick + self.duration:
            return None, None
        tick = tick - self.start_tick
        radius = (float(tick) / float(self.duration)) * self.max_radius
        print radius
        points, faces = circle(radius, 20, self.position)
        return points, faces

class FallingDrop:
    def __init__(self, start=(0,0,50), length=50,size=5, start_tick = 0, duration = 10):
        self.start = start
        self.length = length
        self.duration = duration
        self.start_tick = start_tick
        self.current_tick = 0
        self.size = size

    def get(self, tick):
        if tick < self.start_tick or tick > self.start_tick + self.duration:
            return None, None
        tick = tick - self.start_tick
        z = (float(tick) / float(self.duration)) * self.length
        z = self.length - z
        points, faces = line((self.start[0], self.start[1], z), (self.start[0], self.start[1], z+self.size))
        return points, faces

def main():
    
    

    
    f_index = 0

    #for f in range(10):
    #    points= []
    #    faces = []
    #    line_p , line_f = line((0,0,50-f*5), (0,0,50-f*5-5))
    #    points, faces  = append_shapes(points,faces,line_p,line_f)
    #    model_to_gcode.save_as_gcode(points, faces, create_filename(f_index))
    #    f_index += 1

    d = FallingDrop(start_tick = 0, duration = 10)
    c1 = ExpandingCircle(start_tick = 10, duration = 10)
    c2 = ExpandingCircle(start_tick = 15, duration = 5)



    for tick in range(30):
        points= []
        faces = []
        points,faces = append_shapes((points, faces), c1.get(tick))
        points,faces = append_shapes((points, faces), c2.get(tick))
        print points
        points,faces = append_shapes((points, faces), d.get(tick))
        model_to_gcode.save_as_gcode(points, faces, create_filename(f_index))
        f_index += 1


    
    #points = model_manipulation.center_points(points)
    maxmin = model_manipulation.max_min_values(points)
    print maxmin
    #faces = model_manipulation.order_faces(points, faces)
    
    return


if __name__ == '__main__':
    main()
