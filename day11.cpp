#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
  ifstream input_file("inputfile.txt");
  string line;
  int count;
  if (input_file.is_open()) {
    int curr = 50;
    while (getline(input_file, line)) {
      cout << count << endl;
      char dir = line[0];
      line.erase(line.begin() + 0);
      int val = atoi(line.c_str());
      if (val > 100) {
        // count = count + (val / 100);
        val = val % 100;
      }
      // cout << dir << val;
      if (dir == 'L') {
        if (val > curr) {
          curr = 100 - (val - curr);
          if (curr != 0) {
            // count++;
          }
        } else {
          if (curr == 0)
            curr = 100;
          curr = curr - val;
        }
      } else {
        if (val >= (100 - curr)) {
          curr = abs((100 - (curr + val)));
          if (curr != 0) {
            // count++;
          }
        } else {
          curr = curr + val;
        }
      }
      // cout << curr << endl;
      if (curr == 100)
        curr = 0;
      if (curr == 0) {
        count++;
      }
    }
    cout << count;
  }
  return 0;
}
