def locate_tile(directions):
    i = 0
    E_dist = 0  # East is 1, West is -1
    NE_dist = 0 # Northeast is 1, Southwest is -1
    NW_dist = 0 # Northwest is 1, Southeast is -1

    # Compute distance traveled in E, NE, and NW directions
    while i < len(directions):
        instr = directions[i]
        if instr == 'e':
            E_dist += 1 # E
        elif instr == 'w':
            E_dist -= 1 # W
        elif instr == 'n':
            i += 1
            instr = directions[i]
            if instr == 'e':
                NE_dist += 1 # NE
            elif instr == 'w':
                NW_dist += 1 # NW
        elif instr == 's':
            i += 1
            instr = directions[i]
            if instr == 'e':
                NW_dist -= 1 # SE
            elif instr == 'w':
                NE_dist -= 1 # SW
        i += 1

    # Represent East as NE followed by SE
    NE_dist += E_dist
    NW_dist -= E_dist

    return (NE_dist, NW_dist)

def get_tile(tiles, location):
    if location in tiles.keys():
        return tiles[location]
    return 0

with open('day24.txt', 'r') as f:
    # Odd number indicates tile is black, even indicates tile is white
    tiles = {}

    # Flip all tiles as specified in input
    for line in f.readlines():
        location = locate_tile(line)
        tiles[location] = 1 - get_tile(tiles, location)

    # Count number of black tiles
    print(sum(tiles.values()))
