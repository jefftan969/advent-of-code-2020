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

def access_seat(seats, row, col):
    num_rows = len(seats)
    num_cols = len(seats[0])
    if (0 <= row and row < num_rows) and (0 <= col and col < num_cols):
        return seats[row][col]
    return 'L'

def count_neighbors(seats, row, col):
    num_neighbors = 0
    for row_diff in [-1,0,1]:
        for col_diff in [-1,0,1]:
            if row_diff != 0 or col_diff != 0:
                if access_seat(seats, row + row_diff, col + col_diff) == '#':
                    num_neighbors += 1
    return num_neighbors

def apply_rules(seats):
    new_seats = [list(row) for row in seats]
    for row in range(len(seats)):
        for col in range(len(seats[0])):
            if seats[row][col] != '.':
                neighbors = count_neighbors(seats, row, col)
                if neighbors == 0:
                    # Empty seat with no adjacent occupied seats becomes occupied
                    new_seats[row][col] = '#'
                elif neighbors >= 4:
                    # Occupied seat with >=4 adjacent occupied seats becomes empty
                    new_seats[row][col] = 'L'
                else:
                    # Otherwise, seat state does not change
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
