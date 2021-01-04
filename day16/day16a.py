import parse

def get_invalid_sum(ticket, valid_ranges):
    invalid_sum = 0
    for num in ticket:
        is_valid = False
        for (range_name, ranges) in valid_ranges.items():
            # Check whether each number on the ticket is contained within some valid range
            (range1_min, range1_max, range2_min, range2_max) = ranges
            if (range1_min <= num and num <= range1_max) or (range2_min <= num and num <= range2_max):
                is_valid = True
        if not is_valid:
            # Track sum of each invalid number on ticket
            invalid_sum += num
    return invalid_sum

with open('day16.txt', 'r') as f:
    valid_ranges = {}
    your_ticket = []
    nearby_tickets = []
    # Parse valid ranges
    while True:
        line = f.readline()
        if line == '\n':
            break
        parsed = parse.parse("{}: {}-{} or {}-{}\n", line)
        range_name = parsed[0]
        range1_min = int(parsed[1])
        range1_max = int(parsed[2])
        range2_min = int(parsed[3])
        range2_max = int(parsed[4])
        valid_ranges[range_name] = (range1_min, range1_max, range2_min, range2_max)

    # Parse your ticket
    line = f.readline() # skip the line "your ticket: "
    line = f.readline()
    your_ticket = [int(n) for n in line.strip().split(',')]

    # Parse nearby tickets
    line = f.readline() # skip empty line
    line = f.readline() # skip the line "nearby tickets: "
    while True:
        line = f.readline()
        if line == '':
            break
        ticket = [int(n) for n in line.strip().split(',')]
        nearby_tickets.append(ticket)

    # Get invalid sum of each nearby ticket
    print(sum(get_invalid_sum(ticket, valid_ranges) for ticket in nearby_tickets))

