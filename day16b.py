import parse

def num_in_range(num, ranges):
    (range1_min, range1_max, range2_min, range2_max) = ranges
    return (range1_min <= num and num <= range1_max) or (range2_min <= num and num <= range2_max)

def get_invalid_sum(ticket, valid_ranges):
    invalid_sum = 0
    for num in ticket:
        is_valid = False
        for (range_name, ranges) in valid_ranges.items():
            # Check whether each number is contained within some valid range on the ticket
            if num_in_range(num, ranges):
                is_valid = True
        if not is_valid:
            # Track sum of each invalid number on ticket
            invalid_sum += num
    return invalid_sum

def position_range_match(valid_tickets, ranges, position):
    # Check whether the number at the given position falls within the given range for every valid ticket
    for ticket in valid_tickets:
        num = ticket[position]
        if not num_in_range(num, ranges):
            return False
    return True

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

    # Filter only for valid tickets
    valid_tickets = [ticket for ticket in nearby_tickets if get_invalid_sum(ticket, valid_ranges) == 0]
    valid_tickets.append(your_ticket)

    # Build position range table
    position_range_matches = {}
    position_range_table = [{range_name:position_range_match(valid_tickets, ranges, position) \
                            for (range_name, ranges) in valid_ranges.items()} \
                            for position in range(len(your_ticket))]
    while True:
        # Try to find a definitive match
        certain_match_found = False
        for position in range(len(your_ticket)):
            table_row = position_range_table[position]
            possible_matches = [range_name for range_name in table_row.keys() if table_row[range_name]]

            # Definitive match found, update position range table to prevent that range from being matched again
            if len(possible_matches) == 1:
                match = possible_matches[0]
                position_range_matches[match] = position
                for pos in range(len(your_ticket)):
                    position_range_table[pos][match] = False
                certain_match_found = True

        # Exit if no definitive match found
        if not certain_match_found:
            break

    # Multiply togther the numbers on your ticket belonging to fields that start with "departure"
    your_departure_product = 1
    for (range_name, position) in position_range_matches.items():
        if "departure" in range_name:
            your_departure_product *= your_ticket[position]
    print(your_departure_product)
