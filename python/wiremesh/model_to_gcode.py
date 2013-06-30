#!/usr/bin/env python

import math
import random
import model_manipulation


def obj_parse(filename):
    f = open(filename)
    verticies = []
    faces = []
    for line in f:
        if line.startswith('v'):
            point = line.split(' ')
            point = point[1:]
            xyz = (float(point[0]), float(point[1]), float(point[2]))
            verticies.append(xyz)
        if line.startswith('f'):
            face_text = line.split(' ')
            face_text = face_text[1:]
            face = []
            for v in face_text:
                if '/' in v:
                    v.split['/']
                    v = v[0]
                face.append(int(v) - 1)
            faces.append(face)
    return (verticies, faces)


def stl_parse(filename):
    f= open(filename)
    verticies = []
    faces = []
    text = f.read()
    text = text.split('\n')

    index = 0
    while True:
        try:
            l = text[index]
            l = l.strip()
        except IndexError:
            break

        if l.startswith("outer loop"):
            index += 1
            l = text[index]
            l = l.strip()
            face = []
            while l.startswith('vertex'):
                v = l.split()
                v = v[1:]
                v = tuple([float(vert) for vert in v])
                if v in verticies:
                    pass 
                else:
                    verticies.append(v)
                face.append(verticies.index(v))
                index += 1
                l = text[index]
                l = l.strip()
            faces.append(face)
        else:
            index += 1
    return (verticies, faces)


def save_as_gcode(points, faces, filename = 'output.gcode'):
    spindle_on = "M3"    
    spindle_off = "M5"
    f = open(filename, 'w')
    drawn = []
    for face in faces:
        for index, vertex_index in enumerate(face):
            if index == 1:
                f.write(spindle_on+'\n')
            vertex = points[vertex_index]
            x = vertex[0]
            y = vertex[1]
            z = vertex[2]
            cmd = "G1 X"+str(x)+" Y"+str(y)+" Z"+str(z)+ " F"+'3200.0'+'\n'
            f.write(cmd)
            drawn.append(cmd)
        f.write(spindle_off+'\n')


    f.close()


def main():
    #points_obj, faces_obj = obj_parse('sphere.obj')
    points, faces = stl_parse('petal.stl')

    points = model_manipulation.scale(points, 1.4)
    
    points = model_manipulation.center_points(points)
    maxmin = model_manipulation.max_min_values(points)
    print maxmin[2]

    model_manipulation.save_as_obj(points, faces)
    faces = model_manipulation.order_faces(points, faces)
    
    save_as_gcode(points, faces)
    return


if __name__ == '__main__':
    main()
