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

# Returns neighbor locations
def get_neighbors(tiles, location):
    (NE_dist, NW_dist) = location
    return [(NE_dist+1, NW_dist-1), # East
            (NE_dist, NW_dist-1),   # Southeast
            (NE_dist-1, NW_dist),   # Southwest
            (NE_dist-1, NW_dist+1), # West
            (NE_dist, NW_dist+1),   # Northwest
            (NE_dist+1, NW_dist)]   # Northeast

# Returns the number of black neighbors
def count_neighbors(tiles, location):
    return sum([get_tile(tiles, neighbor) for neighbor in get_neighbors(tiles, location)])

with open('day24.txt', 'r') as f:
    # Odd number indicates tile is black, even indicates tile is white
    tiles = {}

    # Flip all tiles as specified in input
    for line in f.readlines():
        location = locate_tile(line)
        tiles[location] = 1 - get_tile(tiles, location)

    # Apply rules for given number of days simultaneously to each tile
    for day in range(100):
        new_tiles = {}

        # Consider tiles that are currently marked black, as well as their neighbors
        tiles_to_consider = set(tiles.keys())
        for tile in tiles.keys():
            tiles_to_consider = tiles_to_consider.union(set(get_neighbors(tiles, tile)))

        # Flip each tile to consider according to the rules, only adding black tiles to new_tiles
        for tile in tiles_to_consider:
            num_neighbors = count_neighbors(tiles, tile)
            if get_tile(tiles, tile) == 1:
                # Black tile stays black if it has 1 or 2 black neighbors
                if num_neighbors > 0 and num_neighbors <= 2:
                    new_tiles[tile] = 1
            else:
                # White tile turns black if it has 2 black neighbors
                if num_neighbors == 2:
                    new_tiles[tile] = 1

        tiles = new_tiles

    # Print number of black tiles
    print(sum(tiles.values()))
