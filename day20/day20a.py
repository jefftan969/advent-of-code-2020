def parse_tile_string(tile_string):
    tile_id = tile_string[5:9]
    tile_grid = [list(tile_row) for tile_row in tile_string[11:].split('\n')]
    return (int(tile_id), tile_grid)

def get_tile_edges(tile):
    (tile_id, tile_grid) = tile
    tile_edges = {}
    top = tile_grid[0]
    bottom = tile_grid[-1]
    left = [row[0] for row in tile_grid]
    right = [row[-1] for row in tile_grid]
    tile_edges['T'] = top
    tile_edges['B'] = bottom
    tile_edges['L'] = left
    tile_edges['R'] = right
    tile_edges['TR'] = top[::-1]
    tile_edges['BR'] = bottom[::-1]
    tile_edges['LR'] = left[::-1]
    tile_edges['RR'] = right[::-1]
    return tile_edges

with open('day20.txt', 'r') as f:
    tiles = [parse_tile_string(tile_string) for tile_string in f.read().strip().split('\n\n')]
    print(tiles[0])

    # For every edge, track the tiles in which it appears
    edge_to_tiles = {}
    for tile in tiles:
        tile_edges = get_tile_edges(tile)
        for (location, edge) in tile_edges.items():
            edge_str = ''.join(edge)
            if edge_str in edge_to_tiles.keys():
                edge_to_tiles[edge_str].append((tile, location))
            else:
                edge_to_tiles[edge_str] = [(tile, location)]

    # Count number of times each edge appears
    edge_appearances = {edge_str:len(tile_list) for (edge_str, tile_list) in edge_to_tiles.items()}

    # Define is_neighbor function
    def both_single(edgelist_1, edgelist_2):
        edgestr_1 = ''.join(edgelist_1)
        edgestr_2 = ''.join(edgelist_2)
        return (edge_appearances[edgestr_1] + edge_appearances[edgestr_2] == 2)

    # Iterate through each tile, seeing if there are two neighboring edges that appear only once
    corner_tiles = []
    for tile in tiles:
        tile_edges = get_tile_edges(tile)
        if both_single(tile_edges['L'], tile_edges['T']) or \
           both_single(tile_edges['T'], tile_edges['R']) or \
           both_single(tile_edges['R'], tile_edges['B']) or \
           both_single(tile_edges['B'], tile_edges['L']) or \
           both_single(tile_edges['LR'], tile_edges['TR']) or \
           both_single(tile_edges['TR'], tile_edges['RR']) or \
           both_single(tile_edges['RR'], tile_edges['BR']) or \
           both_single(tile_edges['BR'], tile_edges['LR']):
               corner_tiles.append(tile[0])

    print(corner_tiles)
    corner_prod = 1
    for tile_id in corner_tiles:
        corner_prod *= tile_id
    print(corner_prod)
