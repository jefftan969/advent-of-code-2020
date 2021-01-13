#!/usr/bin/python3

with open('day04.txt', 'r') as f:
    valid_count = 0
    fields = {'byr': 0, 'iyr': 0, 'eyr': 0, 'hgt': 0, 'hcl': 0, 'ecl': 0, 'pid': 0}
    lines = f.readlines()
    for line in lines:
        # If line is empty, check if previous passport is valid
        if line == '\n':
            is_valid = True
            for key in fields.keys():
                if fields[key] == 0:
                    is_valid = False
                fields[key] = 0
            if is_valid:
                valid_count += 1
        # If line is nonempty, find any valid tokens in that line
        else:
            for key in fields.keys():
                if fields[key] == 0 and ((key + ':') in line):
                    fields[key] = 1

    print(valid_count)
