#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DSU {
public:
  vector<long long> parent;
  vector<long long> sz;
  DSU(long long n) {
    parent.resize(n);
    sz.resize(n);
    for (long long i = 0; i < n; i++) {
      parent[i] = i;
      sz[i] = 1;
    }
  }
  long long parentfind(long long x) {
    if (parent[x] == x)
      return x;
    parent[x] = parentfind(parent[x]);
    return parent[x];
  }
  bool unite(long long a, long long b) {
    a = parentfind(a);
    b = parentfind(b);
    if (a == b) {
      return false;
    }
    if (sz[a] < sz[b]) {
      swap(a, b);
    }
    parent[b] = a;
    sz[a] += sz[b];
    return true;
  }
};

long long dist(vector<long long> p1, vector<long long> p2) {
  long long dx = (long long)p1[0] - (long long)p2[0];
  long long dy = (long long)p1[1] - (long long)p2[1];
  long long dz = (long long)p1[2] - (long long)p2[2];
  return dx * dx + dy * dy + dz * dz;
}

bool compare(pair<long long, pair<long long, long long>> &a,
             pair<long long, pair<long long, long long>> &b) {
  return a.first < b.first;
}

int main() {
  ifstream input_file("inputfile.txt");
  vector<vector<long long>> points;
  string line;
  while (getline(input_file, line)) {
    vector<string> parts;
    boost::split(parts, line, boost::is_any_of(","));
    for (long long i = 0; i < 3; i++) {
      boost::trim(parts[i]);
    }
    vector<long long> point(3);
    point[0] = stol(parts[0]);
    point[1] = stol(parts[1]);
    point[2] = stol(parts[2]);
    points.push_back(point);
  }

  long long n = points.size();
  vector<pair<long long, pair<long long, long long>>> edges;
  for (long long i = 0; i < n; i++) {
    for (long long j = i + 1; j < n; j++) {
      edges.push_back({dist(points[i], points[j]), {i, j}});
    }
  }
  sort(edges.begin(), edges.end(), compare);

  DSU dsu(n);
  // connect two two together, rest all dsu will long internally do
  for (long long i = 0; i < 1000; i++) {
    long long a = edges[i].second.first;
    long long b = edges[i].second.second;
    dsu.unite(a, b);
  }
  // will visit every junc box and ask which parent/node you are in, if not then
  // np, dont be salty, uss index pe it will add, like each node ke kitte child,
  // that means total connections.
  vector<long long> cnt(n, 0);
  for (long long i = 0; i < n; i++) {
    long long r = dsu.parentfind(i);
    cnt[r]++;
  }
  sort(cnt.begin(), cnt.end(), greater<long long>());
  // for (auto i : cnt)
  // cout << i << " ";

  long long ans = 1;
  ans *= (long long)cnt[0];
  ans *= (long long)cnt[1];
  ans *= (long long)cnt[2];
  cout << ans;
  return 0;
}
