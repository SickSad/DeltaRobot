#!/usr/bin/env python
import model_manipulation
import model_to_gcode
import tween
import random
import math
from random import randint


def circle(position, radius=10.0, degree_steps=10):
    points = []
    face = []
    points = model_manipulation.generate_circle(radius, degree_steps)
    points = model_manipulation.add_offset(points, position)
    face = range(len(points))
    face.append(0)
    return points, face

def line(start, end):
    points = model_manipulation.generate_line(start, end)
    face = range(len(points))
    return points, face



def add_shape((points, faces), (new_points, new_face)):
    if new_face == None or new_points == None:
        return (points, faces)
    new_face = [f+len(points) for f in new_face]
    faces.append(new_face)
    points += new_points
    return (points, faces)

def add_object((points, faces), (new_points, new_faces)):
    if new_faces == None or new_points == None:
        return (points, faces)
    for new_face in new_faces:
        new_face = [f+len(points) for f in new_face]
        faces.append(new_face)
    points += new_points
    return points, faces



class ExpandingCircleAnimation:
    def __init__(self, position, start_tick, end_tick, tween_function, begin_radius, end_radius, degree_steps=20.0):
        self.start_tick = start_tick
        self.end_tick = end_tick
        self.tween_function = tween_function
        self.begin_radius = begin_radius
        self.end_radius = end_radius
        self.position = position
        self.degree_steps = degree_steps

    def get(self, tick):

        if tick < self.start_tick or tick >= self.end_tick:
            return None, None

        time = tick - self.start_tick 
        begin = self.begin_radius
        change = self.end_radius - self.begin_radius
        duration = self.end_tick - self.start_tick
        radius = self.tween_function(time, begin, change, duration)
        points, faces =  circle(self.position, radius, int(self.degree_steps))
        return (points, faces)


class FallingLineAnimation:
    def __init__(self, position, start_tick, end_tick, tween_function, begin_z, end_z, length = 5.0):
        self.start_tick = start_tick
        self.end_tick = end_tick
        self.tween_function = tween_function
        self.begin_z = begin_z
        self.end_z = end_z
        self.position = position
        self.length = length

    def get(self, tick):

        if tick < self.start_tick or tick >= self.end_tick:
            return None, None

        time = tick - self.start_tick 
        begin = self.begin_z
        change = self.end_z - self.begin_z
        duration = self.end_tick - self.start_tick
        z = self.tween_function(time, begin, change, duration)
        l_start = (self.position[0], self.position[1], z)
        l_end = (self.position[0], self.position[1], z - self.length)

        points, faces =  line(l_start, l_end)
        return (points, faces)

class RainDropAnimation:
    def __init__(self, position, start_tick, end_tick, height=50.0, radius=30.0, loop=False, debug =False):
        self.loop = loop
        self.debug = debug
        self.start_tick = start_tick
        self.end_tick = end_tick
        self.height = height
        self.radius = radius
        self.duration = self.end_tick - self.start_tick
        self.drop = FallingLineAnimation(position, start_tick, start_tick+self.duration/2.0, tween.ease_in_quad, position[2]+height, position[2], 5.0)
        self.ripple1 = ExpandingCircleAnimation(position,(start_tick+(self.duration/2.0)),(start_tick+self.duration),tween.ease_out_quad, 0.0,radius)
        #self.ripple2 = ExpandingCircleAnimation(position,(start_tick+(duration/6.0)*3.0),(start_tick+(duration/6.0)*6.0),tween.ease_out_quad, 0.0,radius)

    def get(self, tick):
        if self.loop:
            tick = math.fabs(math.fmod(tick,self.duration))
        if self.debug:
            print tick
        points = []
        faces = []
        points, faces = add_shape((points, faces), self.drop.get(tick))
        points, faces = add_shape((points, faces), self.ripple1.get(tick))
        return points, faces



def main():
    points = []
    faces = []

    #c = ExpandingCircleAnimation((0.0,0.0,10.0),0,10,tween.ease_out_quad, 0.0,10.0, 10.0)
    #for tick in range(1, 10):
    #    points, faces = add_shape((points, faces),c.get(tick))

    #points, faces = add_shape((points, faces),c.get(9))
    
    #r = FallingLineAnimation((0.0,0.0,0.0), 0.0, 20.0, tween.ease_in_quad, 90, 0, length = 5.0)
    #for tick in range(20):
    #    points, faces = add_shape((points, faces),r.get(tick))
    #points, faces = add_shape((points, faces),r.get(1))

    d1 = RainDropAnimation((20.0,20.0,0.0), 0.0, 30.0, 80.0, 20.0, loop=True)
    d2 = RainDropAnimation((0.0,20.0,0.0), 0.0, 30.0, 80.0, 20.0, loop=True)
    d3 = RainDropAnimation((-20.0,20.0,0.0), 0.0, 30.0, 80.0, 20.0, loop=True)
    
    d4 = RainDropAnimation((20.0,0.0,0.0), 0.0, 30.0, 80.0, 20.0, loop=True)
    d5 = RainDropAnimation((0.0,0.0,0.0), 0.0, 30.0, 80.0, 20.0, loop=True)
    d6 = RainDropAnimation((-20.0,0.0,0.0), 0.0, 30.0, 80.0, 20.0, loop=True)
    
    d7 = RainDropAnimation((20.0,-20.0,0.0), 0.0, 30.0, 80.0, 20.0, loop=True)
    d8 = RainDropAnimation((0.0,-20.0,0.0), 0.0, 30.0, 80.0, 20.0, loop=True)
    d9 = RainDropAnimation((-20.0,-20.0,0.0), 0.0, 30.0, 80.0, 20.0, loop=True)


    points = []
    faces = []
    duration = 60

    o1 = randint(0,30)
    o2 = randint(0,30)
    o3 = randint(0,30)
    o4 = randint(0,30)
    o5 = randint(0,30)
    o6 = randint(0,30)
    o7 = randint(0,30)
    o8 = randint(0,30)
    o9 = randint(0,30)

    for tick in range(30):
        points = []
        faces = []
        #   points, faces = add_shape((points, faces),d.get(tick))
        points, faces = add_object((points, faces),d1.get(tick+o1))
        points, faces = add_object((points, faces),d2.get(tick+o2))
        points, faces = add_object((points, faces),d3.get(tick+o3))
        points, faces = add_object((points, faces),d4.get(tick+o4))
        points, faces = add_object((points, faces),d5.get(tick+o5))
        points, faces = add_object((points, faces),d6.get(tick+o6))
        points, faces = add_object((points, faces),d7.get(tick+o7))
        points, faces = add_object((points, faces),d8.get(tick+o8))
        points, faces = add_object((points, faces),d9.get(tick+o9))
        #print points
        #print faces

        filename = str(tick).zfill(3)+".gcode"
        model_to_gcode.save_as_gcode(points, faces, filename)


    print points
    print faces


if __name__ == "__main__":
    main()
