def get_seat_id(line):
    row_str = line[:7]
    col_str = line[7:]

    # Do binary search as instructed to find seat row and column, then find seat ID
    row_lo = 0
    row_hi = 127
    for i in range(0,7):
        if row_str[i] == 'B':
            row_lo = (row_lo + row_hi) // 2 + 1
        elif row_str[i] == 'F':
            row_hi = (row_lo + row_hi) // 2

    col_lo = 0
    col_hi = 7
    for i in range(0,3):
        if col_str[i] == 'R':
            col_lo = (col_lo + col_hi) // 2 + 1
        elif col_str[i] == 'L':
            col_hi = (col_lo + col_hi) // 2

    return 8*row_lo + col_lo

with open('day05.txt', 'r') as f:
    seat_ids = [get_seat_id(line) for line in f]
    seat_ids.sort()

    # Find the missing seat ID
    for i in range(seat_ids[0], seat_ids[-1]):
        if i not in seat_ids:
            print(i)
            break
