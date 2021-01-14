#!/usr/bin/python3

import parse

def parse_bag_contents(content_str):
    plural = parse.parse("{} {} bags", content_str)
    if plural is None:
        singular = parse.parse("1 {} bag", content_str)
        color = singular[0]
        return (color, 1)
    else:
        amount = int(plural[0])
        color = plural[1]
        return (color, amount)

def parse_line(line):
    parsed = parse.parse("{} bags contain {}.", line)
    bag_color = parsed[0]
    bag_content_string = parsed[1]
    if bag_content_string == "no other bags":
        return (bag_color, {})
    else:
        bag_content_strings = bag_content_string.split(", ")
        bag_contents = {key:value for (key, value) in [parse_bag_contents(s) for s in bag_content_strings]}
        return (bag_color, bag_contents)

# Recursively find how many bags are contained within a given bag color
def find_contained_amount(bags, color):
    contained_amt = 0
    for (bag, amount) in bags[color].items():
        contained_amt += amount * (1 + find_contained_amount(bags, bag))
    return contained_amt

with open('day07.txt', 'r') as f:
    # Parse bag rules into a dict representation
    # Example: light red bags contain 1 bright white bag, 2 muted yellow bags.
    #          {'light red': {'bright white': 1, 'muted yellow': 2}}
    bags = {key:value for (key, value) in [parse_line(line) for line in f.readlines()]}

    # Print result
    print(find_contained_amount(bags, 'shiny gold'))
