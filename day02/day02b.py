#!/usr/bin/python3

import parse

def validate_line(line):
    # Parse line into left and right index, desired char, and password
    parsed = parse.parse("{}-{} {}: {}", line)
    indexL = int(parsed[0]) - 1 # Switch from 1-indexing to 0-indexing
    indexR = int(parsed[1]) - 1
    char = parsed[2]
    password = parsed[3]

    char_amt = (password[indexL] == char) + (password[indexR] == char)
    return char_amt == 1

with open('day02.txt', 'r') as f:
    num_valid = sum(1 for line in f if validate_line(line))
    print(num_valid)
