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

with open('day07.txt', 'r') as f:
    # Parse bag rules into a dict representation
    # Example: light red bags contain 1 bright white bag, 2 muted yellow bags.
    #          {'light red': {'bright white': 1, 'muted yellow': 2}}
    bags = {key:value for (key, value) in [parse_line(line) for line in f.readlines()]}

    # For each bag, create list of parent bags that contain it
    bag_parents = {key:[] for (key, value) in bags.items()}
    for (parent, contained_bags) in bags.items():
        for bag in contained_bags.keys():
            bag_parents[bag].append(parent)

    # Use BFS to find all bags that eventually contain a shiny gold bag
    queue = list(bag_parents['shiny gold'])
    visited = {key:False for (key, value) in bags.items()}
    visited['shiny gold'] = True
    valid_set = set(bag_parents['shiny gold'])
    while len(queue) > 0:
        elem = queue.pop()
        if not visited[elem]:
            visited[elem] = True
            valid_set = valid_set.union(set(bag_parents[elem]))
            queue = queue + bag_parents[elem]

    # Print result
    print(len(valid_set))
