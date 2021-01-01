horizontal_offset = 3
vertical_offset = 1

with open('day03.txt', 'r') as f:
    slope = f.readlines()
    width = len(slope[0]) - 1
    height = len(slope)

    count = 0
    # For each row, use modular arithmetic to determine which column to consider
    for row in range(0, height, vertical_offset):
        col = (horizontal_offset * row // vertical_offset) % width
        if slope[row][col] == '#':
            count += 1
    print(count)
