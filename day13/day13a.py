#!/usr/bin/python3

with open('day13.txt', 'r') as f:
    lines = f.readlines()
    start = int(lines[0])
    buses = [int(elem) for elem in lines[1].split(',') if elem != 'x']
    min_diff = start
    min_bus = -1
    for bus in buses:
        # Search through each bus, computing the difference from 'start' until the next multiple of bus
        diff = (bus - (start % bus)) % bus
        if min_diff > diff:
            min_diff = diff
            min_bus = bus
    print(min_bus * min_diff)

