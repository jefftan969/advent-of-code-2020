# Creates empty grid that's 1 unit larger in every direction compared to 'grid'
def expand_grid(grid):
    (_, size_z, size_y, size_x) = grid
    size_z += 1
    size_y += 1
    size_x += 1
    grid_cells = [[['.' for x in range(2*size_x + 1)] for y in range(2*size_y + 1)] for z in range(2*size_z + 1)]
    return (grid_cells, size_z, size_y, size_x)

def access_grid(grid, z, y, x):
    (grid_cells, size_z, size_y, size_x) = grid
    if (-size_z <= z and z <= size_z) and (-size_y <= y and y <= size_y) and (-size_x <= x and x <= size_x):
        return grid_cells[z+size_z][y+size_y][x+size_x]
    return '.'

def set_grid(grid, z, y, x, val):
    (grid_cells, size_z, size_y, size_x) = grid
    if (-size_z <= z and z <= size_z) and (-size_y <= y and y <= size_y) and (-size_x <= x and x <= size_x):
        grid_cells[z+size_z][y+size_y][x+size_x] = val

def count_neighbors(grid, z, y, x):
    num_neighbors = 0
    for z_diff in [-1,0,1]:
        for y_diff in [-1,0,1]:
            for x_diff in [-1,0,1]:
                if (z_diff != 0) or (y_diff != 0) or (x_diff != 0):
                    num_neighbors += (access_grid(grid, z+z_diff, y+y_diff, x+x_diff) == '#')
    return num_neighbors

with open('day17.txt', 'r') as f:
    # Grids are 3D arrays indexed by z, y, x, with additional fields to hold their size
    lines = f.read().strip().split('\n')
    init_grid_cells = [list(line) for line in lines]

    # Ensure grid has odd width/height
    if len(lines[0]) % 2 == 0:
        for i in range(len(lines)):
            init_grid_cells[i].append('.')
    if len(lines) % 2 == 0:
        init_grid_cells.append(['.' for char in init_grid_cells[0]])
    
    grid = ([init_grid_cells], 0, (len(init_grid_cells) - 1) // 2, (len(init_grid_cells[0]) - 1) // 2)

    for iters in range(6):
        # Expand and step grid
        new_grid = expand_grid(grid)
        (_, size_z, size_y, size_x) = new_grid
        for z in range(-size_z, size_z+1):
            for y in range(-size_y, size_y+1):
                for x in range(-size_x, size_x+1):
                    num_neighbors = count_neighbors(grid, z, y, x)
                    curr_cell = access_grid(grid, z, y, x)
                    if curr_cell == '#':
                        # Active cube with exactly 2 or 3 active neighbors, remains active
                        if num_neighbors == 2 or num_neighbors == 3:
                            set_grid(new_grid, z, y, x, '#')
                        else:
                            set_grid(new_grid, z, y, x, '.')
                    elif curr_cell == '.':
                        # Inactive cube with exactly 3 active neighbors, becomes active
                        if num_neighbors == 3:
                            set_grid(new_grid, z, y, x, '#')
                        else:
                            set_grid(new_grid, z, y, x, '.')
        grid = new_grid

    print(sum(sum(sum(1 for cell in xlayer if cell == '#') for xlayer in xylayer) for xylayer in grid[0]))
