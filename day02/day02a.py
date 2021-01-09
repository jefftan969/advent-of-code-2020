#!/usr/bin/python3

import parse

# Counts occurrences of character <char> in <string>
def count_char(string, char):
    return sum(1 for c in string if c == char)

def validate_line(line):
    # Parse line into min and max occurrences, desired char, and password
    parsed = parse.parse("{}-{} {}: {}", line)
    min_amt = int(parsed[0])
    max_amt = int(parsed[1])
    char = parsed[2]
    password = parsed[3]

    char_amt = count_char(password, char)
    return (min_amt <= char_amt) and (char_amt <= max_amt)

with open('day02.txt', 'r') as f:
    num_valid = sum(1 for line in f if validate_line(line))
    print(num_valid)
