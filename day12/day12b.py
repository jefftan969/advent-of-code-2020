#!/usr/bin/python3

import math

with open('day12.txt', 'r') as f:
    lines = f.readlines()
    shipX = 0
    shipY = 0
    wayX = 10
    wayY = 1
    for line in lines:
        action = line[0]
        value = int(line[1:])
        if action == 'N':
            wayY += value
        elif action == 'S':
            wayY -= value
        elif action == 'E':
            wayX += value
        elif action == 'W':
            wayX -= value
        elif action == 'L':
            # Rotate (wayX, wayY) counterclockwise by multiplying by 2x2 rotation matrix
            theta = math.radians(value)
            (wayX, wayY) = (wayX * math.cos(theta) - wayY * math.sin(theta), \
                            wayX * math.sin(theta) + wayY * math.cos(theta))
        elif action == 'R':
            # Rotate (wayX, wayY) clockwise by multiplying by 2x2 rotation matrix
            theta = -math.radians(value)
            (wayX, wayY) = (wayX * math.cos(theta) - wayY * math.sin(theta), \
                            wayX * math.sin(theta) + wayY * math.cos(theta))
        elif action == 'F':
            shipX += value * wayX
            shipY += value * wayY

    print(round(abs(shipX) + abs(shipY)))
