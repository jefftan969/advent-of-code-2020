def check_slope(slope, horizontal_offset, vertical_offset):
    width = len(slope[0]) - 1
    height = len(slope)

    count = 0
    # For each row, use modular arithmetic to determine which column to consider
    for row in range(0, height, vertical_offset):
        col = (horizontal_offset * row // vertical_offset) % width
        if slope[row][col] == '#':
            count += 1
    return count

with open('day03.txt', 'r') as f:
    slope = f.readlines()
    result11 = check_slope(slope, 1, 1)
    result31 = check_slope(slope, 3, 1)
    result51 = check_slope(slope, 5, 1)
    result71 = check_slope(slope, 7, 1)
    result12 = check_slope(slope, 1, 2)
    print(result11 * result31 * result51 * result71 * result12)
