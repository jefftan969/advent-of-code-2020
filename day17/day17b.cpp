#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// Creates an empty grid spanning coordinates (-size_x, -size_y, -size_z) to (size_x, size_y, size_z)
std::tuple<std::vector<std::vector<std::vector<std::vector<char>>>>, int, int, int, int> make_grid(
    int size_w, int size_z, int size_y, int size_x) {
  std::tuple<std::vector<std::vector<std::vector<std::vector<char>>>>, int, int, int, int> grid;
  std::get<1>(grid) = size_w;
  std::get<2>(grid) = size_z;
  std::get<3>(grid) = size_y;
  std::get<4>(grid) = size_x;

  for(int w = -size_w; w <= size_w; w++) {
    std::vector<std::vector<std::vector<char>>> xyz_slice;
    for(int z = -size_z; z <= size_z; z++) {
      std::vector<std::vector<char>> xy_slice;
      for(int y = -size_y; y <= size_y; y++) {
        std::vector<char> x_slice;
        for(int x = -size_x; x <= size_x; x++) {
          x_slice.push_back('.');
        }
        xy_slice.push_back(x_slice);
      }
      xyz_slice.push_back(xy_slice);
    }
    std::get<0>(grid).push_back(xyz_slice);
  }

  return grid;
}

// Creates an empty grid that's 1 unit larger in every direction compared to input grid
std::tuple<std::vector<std::vector<std::vector<std::vector<char>>>>, int, int, int, int> expand_grid(
    const std::tuple<std::vector<std::vector<std::vector<std::vector<char>>>>, int, int, int, int> &grid) {
  int size_w = std::get<1>(grid);
  int size_z = std::get<2>(grid);
  int size_y = std::get<3>(grid);
  int size_x = std::get<4>(grid);
  return make_grid(size_w + 1, size_z + 1, size_y + 1, size_x + 1);
}

char access_grid(const std::tuple<std::vector<std::vector<std::vector<std::vector<char>>>>, int, int, int, int> &grid, int w, int z, int y, int x) {
  int size_w = std::get<1>(grid);
  int size_z = std::get<2>(grid);
  int size_y = std::get<3>(grid);
  int size_x = std::get<4>(grid);
  if((-size_w <= w && w <= size_w) && (-size_z <= z && z <= size_z) &&
     (-size_y <= y && y <= size_y) && (-size_x <= x && x <= size_x)) {
    return std::get<0>(grid)[w+size_w][z+size_z][y+size_y][x+size_x];
  }
  return '.';
}

void set_grid(std::tuple<std::vector<std::vector<std::vector<std::vector<char>>>>, int, int, int, int> &grid,
              int w, int z, int y, int x, char val) {
  int size_w = std::get<1>(grid);
  int size_z = std::get<2>(grid);
  int size_y = std::get<3>(grid);
  int size_x = std::get<4>(grid);
  if((-size_w <= w && w <= size_w) && (-size_z <= z && z <= size_z) &&
     (-size_y <= y && y <= size_y) && (-size_x <= x && x <= size_x)) {
    std::get<0>(grid)[w+size_w][z+size_z][y+size_y][x+size_x] = val;
  }
}

int count_neighbors(const std::tuple<std::vector<std::vector<std::vector<std::vector<char>>>>, int, int, int, int> &grid, int w, int z, int y, int x) {
  int num_neighbors = 0;
  for(int w_diff = -1; w_diff <= 1; w_diff++) {
    for(int z_diff = -1; z_diff <= 1; z_diff++) {
      for(int y_diff = -1; y_diff <= 1; y_diff++) {
        for(int x_diff = -1; x_diff <= 1; x_diff++) {
          if(w_diff != 0 || z_diff != 0 || y_diff != 0 || x_diff != 0) {
            num_neighbors += (access_grid(grid, w+w_diff, z+z_diff, y+y_diff, x+x_diff) == '#');
          }
        }
      }
    }
  }
  return num_neighbors;
}

int main() {
  // Read input from file
  std::ifstream file("day17.txt");
  std::string line;
  std::vector<std::string> lines;

  while(std::getline(file, line)) {
    if(line != std::string("")) {
      lines.push_back(line);
    }
  }

  // Convert input grid to a 3D array, making sure the array's dimensions are all odd
  // The X dimension ranges from -size_x to size_x, inclusive
  // This representation is most efficient when the grid is dense, alternatively can use a hash table where
  // keys are 
  int width = lines[0].length();
  int height = lines.size();
  int size_x = width / 2;
  int size_y = height / 2;
  int size_z = 0;
  int size_w = 0;

  std::tuple<std::vector<std::vector<std::vector<std::vector<char>>>>, int, int, int, int> grid =
      make_grid(size_w, size_z, size_y, size_x);
  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      std::get<0>(grid)[0][0][y][x] = lines[y][x];
    }
  }

  for(int i = 0; i < 6; i++) {
    // Expand and step grid
    std::tuple<std::vector<std::vector<std::vector<std::vector<char>>>>, int, int, int, int> new_grid =
        expand_grid(grid);
    size_w = std::get<1>(new_grid);
    size_z = std::get<2>(new_grid);
    size_y = std::get<3>(new_grid);
    size_x = std::get<4>(new_grid);

    for(int w = -size_w; w <= size_w; w++) {
      for(int z = -size_z; z <= size_z; z++) {
        for(int y = -size_y; y <= size_y; y++) {
          for(int x = -size_x; x <= size_x; x++) {
            int num_neighbors = count_neighbors(grid, w, z, y, x);
            char curr_cell = access_grid(grid, w, z, y, x);
            if(curr_cell == '#') {
              // Any active cube with exactly 2 or 3 active neighbors becomes active
              if(num_neighbors == 2 || num_neighbors == 3) {
                set_grid(new_grid, w, z, y, x, '#');
              } else {
                set_grid(new_grid, w, z, y, x, '.');
              }
            } else if(curr_cell == '.') {
              // Any inactive cube with exactly 3 active nighbors becomes active
              if(num_neighbors == 3) {
                set_grid(new_grid, w, z, y, x, '#');
              } else {
                set_grid(new_grid, w, z, y, x, '.');
              }
            }
          }
        }
      }
    }
    grid.swap(new_grid);
  }

  // Calculate and print sum
  int amount_active = 0;
  size_w = std::get<1>(grid);
  size_z = std::get<2>(grid);
  size_y = std::get<3>(grid);
  size_x = std::get<4>(grid);
  for(int w = -size_w; w <= size_w; w++) {
    for(int z = -size_z; z <= size_z; z++) {
      for(int y = -size_y; y <= size_y; y++) {
        for(int x = -size_x; x <= size_x; x++) {
          if(access_grid(grid, w, z, y, x) == '#') {
            amount_active++;
          }
        }
      }
    }
  }

  std::cout << amount_active << std::endl;
  return 0;
}
