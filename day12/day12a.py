#!/usr/bin/python3

import math

with open('day12.txt', 'r') as f:
    lines = f.readlines()
    posX = 0
    posY = 0
    theta = 0
    for line in lines:
        action = line[0]
        value = int(line[1:])
        if action == 'N':
            posY += value
        elif action == 'S':
            posY -= value
        elif action == 'E':
            posX += value
        elif action == 'W':
            posX -= value
        elif action == 'L':
            theta += value
        elif action == 'R':
            theta -= value
        elif action == 'F':
            posX += value * math.cos(math.radians(theta))
            posY += value * math.sin(math.radians(theta))

    print(round(abs(posX) + abs(posY)))
