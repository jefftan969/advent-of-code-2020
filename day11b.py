def check_equal(seats1, seats2):
    num_rows = len(seats1)
    num_cols = len(seats1[0])
    if num_rows != len(seats2):
        return False
    if num_cols != len(seats2[0]):
        return False
    for row in range(num_rows):
        for col in range(num_cols):
            if seats1[row][col] != seats2[row][col]:
                return False
    return True

# Returns whether there exists an occupied seat in the given direction from seats[row][col]
def occupied_in_direction(seats, row, col, h_offset, v_offset):
    num_rows = len(seats)
    num_cols = len(seats[0])
    seek_row = row + v_offset
    seek_col = col + h_offset

    while (0 <= seek_row) and (seek_row < num_rows) and (0 <= seek_col) and (seek_col < num_cols):
        if seats[seek_row][seek_col] == '#':
            return True
        elif seats[seek_row][seek_col] == 'L':
            return False
        seek_row += v_offset
        seek_col += h_offset
    return False

# Consider the first visible seat in all eight directions
def count_neighbors(seats, row, col):
    return occupied_in_direction(seats, row, col, -1, 0) + \
           occupied_in_direction(seats, row, col, -1, 1) + \
           occupied_in_direction(seats, row, col, 0, 1) + \
           occupied_in_direction(seats, row, col, 1, 1) + \
           occupied_in_direction(seats, row, col, 1, 0) + \
           occupied_in_direction(seats, row, col, 1, -1) + \
           occupied_in_direction(seats, row, col, 0, -1) + \
           occupied_in_direction(seats, row, col, -1, -1)
    
def apply_rules(seats):
    new_seats = [list(row) for row in seats]
    for row in range(len(seats)):
        for col in range(len(seats[0])):
            if seats[row][col] != '.':
                neighbors = count_neighbors(seats, row, col)
                if neighbors == 0:
                    # Empty seats that see no occupied seats become occupied
                    new_seats[row][col] = '#'
                elif neighbors >= 5:
                    # Occupied seats that see >=5 occupied seats become empty
                    new_seats[row][col] = 'L'
                else:
                    # Otherwise, seat doesn't change
                    new_seats[row][col] = seats[row][col]
    return new_seats

def count_occupants(seats):
    return sum((sum(1 for char in row if char == '#')) for row in seats)

with open('day11.txt', 'r') as f:
    lines = f.read().strip().split('\n')
    seats = [list(line) for line in lines]

    # Keep applying rules until seats no longer change
    while True:
        new_seats = apply_rules(seats)
        if check_equal(seats, new_seats):
            seats = new_seats
            break
        else:
            seats = new_seats

    print(count_occupants(seats))
