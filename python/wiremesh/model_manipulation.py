#!/usr/bin/env python

import math
import random


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


def max_min_values(points):
    max_x = float('-inf')
    max_y = float('-inf')
    max_z = float('-inf')
    min_x = float('inf')
    min_y = float('inf')
    min_z = float('inf')
    for point in points:
        if point[0] > max_x:
            max_x = point[0]
        if point[0] < min_x:
            min_x = point[0]
        if point[1] > max_y:
            max_y = point[1]
        if point[1] < min_y:
            min_y = point[1]
        if point[2] > max_z:
            max_z = point[2]
        if point[2] < min_z:
            min_z = point[2]
    return ((max_x, min_x), (max_y, min_y), (max_z, min_z))


def add_offset(points, (x_offset, y_offset, z_offset)):
    new_points = []
    for index in range(len(points)):
        x = points[index][0] + x_offset
        y = points[index][1] + y_offset
        z = points[index][2] + z_offset
        new_points.append((x, y, z))
    return new_points


def scale(points, scale):
    new_points = []
    for index in range(len(points)):
        x = points[index][0] * scale
        y = points[index][1] * scale
        z = points[index][2] * scale
        new_points.append((x, y, z))
    return new_points


def distance_3D(v1, v2):
    distance = math.sqrt(pow(v1[0] - v2[0], 2) + pow(v1[1] - v2[1], 2) + pow(v1[2] - v2[2], 2))
    return distance


def rotate_z(points, degrees):
    r = math.radians(degrees)
    new_points = []

    for i in range(len(points)):
        x = points[i][0]
        y = points[i][1]
        z = points[i][2]

        x2 = x * math.cos(r) - y * math.sin(r)
        y2 = y * math.cos(r) + x * math.sin(r)

        new_points.append((x2, y2, z))
    return new_points


def rotate_x(points, degrees):
    r = math.radians(degrees)
    new_points = []
    for i in range(len(points)):
        x = points[i][0]
        y = points[i][1]
        z = points[i][2]

        y2 = y * math.cos(r) - z * math.sin(r)
        z2 = z * math.cos(r) + y * math.sin(r)

        new_points.append((x, y2, z2))
    return new_points


def rotate_y(points, degrees):
    r = math.radians(degrees)
    new_points = []
    for i in range(len(points)):
        x = points[i][0]
        y = points[i][1]
        z = points[i][2]

        z2 = z * math.cos(r) - x * math.sin(r)
        x2 = x * math.cos(r) + z * math.sin(r)

        new_points.append((x2, y, z2))
    return new_points


def order_faces(points, faces):
    new_faces = []
    new_faces.append(faces[0])
    faces.remove(new_faces[0])
    while(len(faces) > 0):
        vertex_index = new_faces[-1][-1]
        vertex = points[vertex_index]
        nearest_value = float('inf')
        nearest_face = []
        for face in faces:
            test_vertex_index = face[0]
            test_vertex = points[test_vertex_index]
            distance = distance_3D(vertex, test_vertex)
            if distance < nearest_value:
                nearest_value = distance
                nearest_face = face
        new_faces.append(nearest_face)
        faces.remove(nearest_face)
    return new_faces


def center_points(points):
    (max_x, min_x), (max_y, min_y), (max_z, min_z) = max_min_values(points)
    diff_x = max_x - min_x
    diff_y = max_y - min_y
    diff_z = max_z - min_z
    sub_x = (diff_x / 2) + min_x
    sub_y = (diff_y / 2) + min_y
    sub_z = (diff_z / 2) + min_z

    for index in range(len(points)):
        x = points[index][0] - sub_x
        y = points[index][1] - sub_y
        z = points[index][2] - sub_z
        points[index] = (x, y, z)
    return points


def save_as_obj(points, faces, filename='output.obj'):
    f = open(filename, 'w')
    f.write('o Object\n')
    for point in points:
        f.write('v ' + str(point[0]) + ' ' + str(point[1]) + ' ' + str(point[2]) + '\n')

    f.write('s off\n')
    for face in faces:
        f_str = ''
        for p in face:
            f_str += ' ' + str(p + 1)
        f.write('f' + f_str + '\n')
    f.close()
    return


def generate_circle(raidus=1.0, degree_steps=10):
    points = []
    points.append((raidus, 0, 0))

    for val in range(degree_steps - 1):
        angle = (360.0 / degree_steps) * (val + 1)
        r = math.radians(angle)
        x = points[0][0]
        y = points[0][1]
        z = points[0][2]
        x2 = x * math.cos(r) - y * math.sin(r)
        y2 = y * math.cos(r) + x * math.sin(r)
        z2 = z
        points.append((x2, y2, z2))
    return points

def generate_line(start=(0,0,50), end=(0,0,45)):
    points = [start, end]
    return points


def explode(points, amount, seed):
    #split out faces into groups of points
    random.seed(seed)
    result = []
    for point in points:
        offset = random.random()
        x = point[0]
        y = point[1]
        z = point[2]
        if random.random() > 0.3:
            x += x * amount * offset
            y += y * amount * offset
            z += z * amount * offset
        result.append((x, y, z))
    return result


def main():

    points, faces = obj_parse('sphere.obj')
    new_points = []
    for x in range(20):
        points = explode(points, x / 220.0, 10)
        new_points = rotate_y(points, x * (90.0 / 20.0))
        new_points = scale(new_points, 15)
        new_points = add_offset(new_points, (0.0, 0.0, 20.0))
        print max_min_values(new_points)
        save_as_obj(new_points, faces, str(x).zfill(3) + '.obj')

    return

    p1_points, p1_faces = obj_parse('sphere.obj')
    print len(p1_faces)

    sc = 4.0
    steps = 60
    d_per_s = 360.0 / 60.0
    for r in range(steps):

        p1_points, p1_faces = obj_parse('sphere.obj')
        p1_points = center_points(p1_points)
        p1_points = rotate_x(p1_points, 90.0)
        p1_points = scale(p1_points, 1.0 * sc)
        p1_points = add_offset(p1_points, (8.0 * sc, 0.0, 0.0))
        p1_faces = order_faces(p1_points, p1_faces)
        p1_points = rotate_z(p1_points, 0 + d_per_s * r)
        save_as_obj(p1_points, p1_faces, 'p1.obj')

        p2_points, p2_faces = obj_parse('sphere.obj')
        p2_points = center_points(p2_points)
        p2_points = rotate_x(p2_points, 90.0)
        p2_points = scale(p2_points, 0.6 * sc)
        p2_points = add_offset(p2_points, (5.0 * sc, 0.0, 0.0))
        p2_faces = order_faces(p2_points, p2_faces)
        p2_points = rotate_z(p2_points, 135.0 - d_per_s * r * 2.0)
        save_as_obj(p2_points, p2_faces, 'p2.obj')

        s_points, s_faces = obj_parse('sphere.obj')
        s_points = center_points(s_points)
        s_points = rotate_x(s_points, 90.0)
        s_points = scale(s_points, 2.0 * sc)
        s_points = add_offset(s_points, (0.0 * sc, 0.0, 0.0))
        s_faces = order_faces(s_points, s_faces)
        s_points = rotate_z(s_points, 0.0 + (d_per_s * r) / 4.0)
        save_as_obj(s_points, s_faces, 's.obj')

    return


if __name__ == '__main__':
    main()
