def rotate_right(tile_grid):
    num_rows = len(tile_grid)
    num_cols = len(tile_grid[0])
    return [[tile_grid[num_rows-1-row_id][col_id] for row_id in range(num_rows)] for col_id in range(num_cols)]

def flip_horizontal(tile_grid):
    return [row[::-1] for row in tile_grid]

def split_tile(tile_grid):
    edgeT = tile_grid[0]
    edgeB = tile_grid[-1]
    edgeL = [row[0] for row in tile_grid]
    edgeR = [row[-1] for row in tile_grid]
    tile_mid = [row[1:-1] for row in tile_grid[1:-1]]
    return (edgeT, edgeB, edgeL, edgeR, tile_mid)

def get_orientations(tile_grid):
    orientations = []
    orientations.append(tile_grid)
    orientations.append(rotate_right(orientations[0]))
    orientations.append(rotate_right(orientations[1]))
    orientations.append(rotate_right(orientations[2]))
    orientations.append(flip_horizontal(tile_grid))
    orientations.append(rotate_right(orientations[4]))
    orientations.append(rotate_right(orientations[5]))
    orientations.append(rotate_right(orientations[6]))
    return orientations

def parse_tile_string(tile_string):
    tile_id = int(tile_string[5:9])
    tile_grid = [list(tile_row) for tile_row in tile_string[11:].split('\n')]
    orientations = get_orientations(tile_grid)
    return [(tile_id, i, split_tile(orientations[i])) for i in range(len(orientations))]

with open('day20.txt', 'r') as f:
    tile_strings = f.read().strip().split('\n\n')
    tiles = []
    for tile_string in tile_strings:
        tiles += parse_tile_string(tile_string)

    # For every tile orientation, track its neighbors
    # Note, this duplicates the work needed 4x here, but avoids needing to explicitly track orientations later
    neighbors = [{} for num in range(len(tiles))]
    for i in range(len(tiles)):
        for j in range(i+1, len(tiles)):
            (id_i, orientation_i, (edgeT_i, edgeB_i, edgeL_i, edgeR_i, _)) = tiles[i]
            (id_j, orientation_j, (edgeT_j, edgeB_j, edgeL_j, edgeR_j, _)) = tiles[j]
            if id_i != id_j:
                if edgeT_i == edgeB_j:
                    neighbors[i]['T'] = j
                    neighbors[j]['B'] = i
                elif edgeB_i == edgeT_j:
                    neighbors[i]['B'] = j
                    neighbors[j]['T'] = i
                elif edgeL_i == edgeR_j:
                    neighbors[i]['L'] = j
                    neighbors[j]['R'] = i
                elif edgeR_i == edgeL_j:
                    neighbors[i]['R'] = j
                    neighbors[j]['L'] = i

    # Find the tiles with only two neighbors
    corner_ids = [i for i in range(len(tiles)) if len(neighbors[i].values()) == 2]
    corner_tile_ids = list(set([tiles[i][0] for i in corner_ids]))

    # Determine image tile grid by starting with corner tiles and progressively filling in adjacent tiles
    image_grid_size = int(len(tile_strings)**0.5)
    image_grid = [[None for col_id in range(image_grid_size)] for row_id in range(image_grid_size)]
    image_grid[0][0] = corner_ids[0]
    for row_id in range(image_grid_size):
        for col_id in range(image_grid_size):
            grid_neighbors = neighbors[image_grid[row_id][col_id]]
            if 'T' in grid_neighbors.keys():
                image_grid[row_id-1][col_id] = grid_neighbors['T']
            if 'B' in grid_neighbors.keys():
                image_grid[row_id+1][col_id] = grid_neighbors['B']
            if 'L' in grid_neighbors.keys():
                image_grid[row_id][col_id-1] = grid_neighbors['L']
            if 'R' in grid_neighbors.keys():
                image_grid[row_id][col_id+1] = grid_neighbors['R']

    # Consolidate image grid into a singular 2D image
    tile_size = len(tiles[0][2][4])
    image_size = tile_size * image_grid_size
    image = [[None for col_id in range(image_size)] for row_id in range(image_size)]
    for grid_row in range(image_grid_size):
        for grid_col in range(image_grid_size):
            tile_contents = tiles[image_grid[grid_row][grid_col]][2][4]
            row_offset = tile_size * grid_row
            col_offset = tile_size * grid_col
            for tile_row in range(tile_size):
                for tile_col in range(tile_size):
                    image[row_offset + tile_row][col_offset + tile_col] = tile_contents[tile_row][tile_col]

    # Look for monsters in every possible orientation of the image
    monster = [(0,18),(1,0),(1,5),(1,6),(1,11),(1,12),(1,17),(1,18),(1,19),\
               (2,1),(2,4),(2,7),(2,10),(2,13),(2,16)]
    monster_width = 20
    monster_height = 3
    for image_oriented in get_orientations(image):
        num_monsters = 0
        # Loop through every possible index that the top left of the monster could be at
        for row_id in range(image_size - monster_height):
            for col_id in range(image_size - monster_width):
                monster_found = True
                for (row_offset, col_offset) in monster:
                    # Monster is found if all '#' match with the monster
                    if image_oriented[row_id + row_offset][col_id + col_offset] != '#':
                        monster_found = False
                if monster_found:
                    # If monster is discovered, mark it in the image with 'O'
                    num_monsters += 1
                    for (row_offset, col_offset) in monster:
                        image_oriented[row_id + row_offset][col_id + col_offset] = 'O'
        # If this orientation contains monsters, count the roughness of the water
        if num_monsters > 0:
            print(sum(sum(1 for pixel in image_row if pixel == '#') for image_row in image_oriented))
            break
