#!/usr/bin/python3

def is_between(x, low, high):
    try:
        num = int(x)
        return (low <= num) and (num <= high)
    except:
        return False

# Four digits, at least 1920 and at most 2002
def byr_validfn(x):
    return is_between(x, 1920, 2002)

# Four digits, at least 2010 and at most 2020
def iyr_validfn(x):
    return is_between(x, 2010, 2020)

# Four digits, at least 2020 and at most 2030
def eyr_validfn(x):
    return is_between(x, 2020, 2030)

# A number, either 150cm <= x <= 193cm or 59in <= x <= 76in
def hgt_validfn(x):
    try:
        height = x[:-2]
        unit = x[-2:]
        if unit == 'cm':
            return is_between(height, 150, 193)
        elif unit == 'in':
            return is_between(height, 59, 76)
        else:
            return False
    except:
        return False

# A '#' followed by exactly six hexadecimal characters 0-9 or a-f
def hcl_validfn(x):
    try:
        valid_chars = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
        if len(x) != 7:
            return False
        if x[0] != '#':
            return False
        for i in range(1,7):
            if x[i] not in valid_chars:
                return False
        return True
    except:
        return False

# Exactly one of a given list
def ecl_validfn(x):
    try:
        valid_ecls = ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']
        return (x in valid_ecls)
    except:
        return False

# A nine-digit number including leading zeroes
def pid_validfn(x):
    try:
        valid_chars = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
        if len(x) != 9:
            return False
        for i in range(0,9):
            if x[i] not in valid_chars:
                return False
        return True
    except:
        return False

def check_valid(passport_str, criteria):
    # Build passport dict from passport_str
    passport = {}
    entries = passport_str.split()
    for entry in entries:
        [key, value] = entry.split(':')
        passport[key] = value

    # Call each criteria function to make sure that criterion is valid
    for key in criteria.keys():
        value = passport.get(key)
        if value is None:
            return False
        if (criteria[key])(value) == False:
            return False
    return True

with open('day04.txt', 'r') as f:
    criteria = {'byr': byr_validfn,
                'iyr': iyr_validfn,
                'eyr': eyr_validfn,
                'hgt': hgt_validfn,
                'hcl': hcl_validfn,
                'ecl': ecl_validfn,
                'pid': pid_validfn}

    all_lines = f.read()
    passport_strings = all_lines.split('\n\n')
    num_valid = sum(1 for s in passport_strings if check_valid(s, criteria))
    print(num_valid)
