#!/usr/bin/python3

with open('day06.txt', 'r') as f:
    all_lines = f.read() + '\n'
    group_strings = all_lines.split('\n\n')
    groups = [group_str.split('\n') for group_str in group_strings]
    setlists = [[set(person) for person in group] for group in groups]
    set_intersections = [set.intersection(*setlist) for setlist in setlists]
    group_counts = [len(s) for s in set_intersections]
    print(sum(group_counts))

# One line solution:
# print(sum([len(set.intersection(*([set(person) for person in group_str.split('\n')]))) for group_str in (open('day06.txt', 'r').read()+'\n').split('\n\n')]))
