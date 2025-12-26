#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

// hash func picked up from gfg:
// https://www.geeksforgeeks.org/cpp/how-to-create-an-unordered_map-of-pairs-in-c/
struct hash_pair {
  template <class T1, class T2> size_t operator()(const pair<T1, T2> &p) const {
    // Hash the first element
    size_t hash1 = hash<T1>{}(p.first);
    // Hash the second element
    size_t hash2 = hash<T2>{}(p.second);
    // Combine the two hash values
    return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
  }
};

long long dpcalc(vector<vector<char>> &grid, int x, int y,
                 unordered_map<pair<int, int>, long long, hash_pair> &cmap) {

  if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()) {
    return 0;
  }

  pair<int, int> curr = {x, y};
  if (cmap.count(curr)) {
    return cmap[curr];
  }

  if (x + 1 >= grid.size()) {
    return 1;
  }

  long long total = 0;

  if (grid[x + 1][y] == '.' || grid[x + 1][y] == 'S') {
    total += dpcalc(grid, x + 1, y, cmap);
  } else if (grid[x + 1][y] == '^') {
    total += dpcalc(grid, x + 1, y + 1, cmap);
    total += dpcalc(grid, x + 1, y - 1, cmap);
  }

  cmap[curr] = total;
  return total;
}

int main() {
  string line;
  ifstream input_file("inputfile.txt");
  vector<vector<char>> grid;

  if (input_file.is_open()) {
    while (getline(input_file, line)) {
      vector<char> row;
      for (char c : line) {
        row.push_back(c);
      }
      grid.push_back(row);
    }
  }
  // cout << grid[0][0];
  int start_col = -1;
  for (int i = 0; i < grid[0].size(); i++) {
    if (grid[0][i] == 'S') {
      start_col = i;
      break;
    }
  }
  unordered_map<pair<int, int>, long long, hash_pair> cmap;
  long long total = dpcalc(grid, 0, start_col, cmap);
  cout << total;
  return 0;
}
