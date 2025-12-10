#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int split(const vector<vector<char>> &grid, int row, int col,
          vector<int> &splitted, vector<vector<bool>> &visited) {
  int nextRow = row + 1;
  if (nextRow < 0 || nextRow >= grid.size()) {
    return 0;
  }
  if (col < 0 || col >= grid[nextRow].size()) {
    return 0;
  }
  if (visited[nextRow][col]) {
    return 0;
  }
  visited[nextRow][col] = true;

  if (grid[nextRow][col] == '.') {
    return split(grid, nextRow, col, splitted, visited);
  } else if (grid[nextRow][col] == '^') {
    splitted.push_back(1);
    return 1 + split(grid, nextRow, col - 1, splitted, visited) +
           split(grid, nextRow, col + 1, splitted, visited);
  }
  return 0;
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
  vector<int> splits;
  vector<vector<bool>> visited(grid.size(),
                               vector<bool>(grid[0].size(), false));
  int total = split(grid, 0, start_col, splits, visited);
  cout << total;
  return 0;
}
