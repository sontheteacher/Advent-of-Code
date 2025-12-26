#include "helper.h"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>

using namespace std;
typedef long long ll;
typedef vector<string> vs;
typedef pair<long, pair<int, int>> Edge;

struct UnionFind {
  vector<int> parent; // keep track by indices
  vector<int> sz;     // size of each circuit

  UnionFind(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0); // each box is independent
    sz.assign(n, 1); // each circuit contain 1 box initially
  }

  // Find with path compression
  int find(int i) {
    if (parent[i] == i)
      return i;
    return parent[i] = find(parent[i]);
  }

  // Union by size
  void unite(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);
    if (root_u != root_v) {
      if (sz[root_u] > sz[root_v])
        swap(root_u, root_v);
      parent[root_u] = root_v;
      sz[root_v] += sz[root_u];
    }
  }

  vector<int> curr_sizes() {
    vector<int> current_size;
    for (int i = 0; i < int(parent.size()); ++i) {
      if (i == parent[i])
        current_size.push_back(sz[i]);
    }

    return current_size;
  }
};

vector<int> parse_coords(const string &line) {
  vs s = split(line, ',');
  return {stoi(s[0]), stoi(s[1]), stoi(s[2])};
}

ll part_1(const string &input) {
  // NOTE: Initialize the coordinates
  vs lines = read_input(input);
  vector<vector<int>> coords;
  transform(lines.begin(), lines.end(), back_inserter(coords), parse_coords);

  priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
  for (size_t i = 0; i < coords.size() - 1; ++i) {
    for (size_t j = i + 1; j < coords.size(); ++j) {
      int dx = coords[i][0] - coords[j][0];
      int dy = coords[i][1] - coords[j][1];
      int dz = coords[i][2] - coords[j][2];
      long dist = 1L * dx * dx + 1L * dy * dy + 1L * dz * dz;
      pq.push({dist, {i, j}});
    }
  }

  UnionFind elements(coords.size());
  int n_connections = 1000;
  for (int i : std::views::iota(0, n_connections)) {
    auto [dist, nodes] = pq.top();
    pq.pop();
    elements.unite(nodes.first, nodes.second);
  }

  // grab top 3 elements
  vector<int> sizes = elements.curr_sizes();
  ll res = 1;
  nth_element(sizes.begin(), sizes.begin() + 3, sizes.end(),
              std::greater<int>());
  for (int i : views::iota(0, 3)) {
    res *= sizes[i];
  }
  return res;
}

ll part_2(const string &line) {
  vs lines = read_input(line);

  vector<vector<int>> coords;
  transform(lines.begin(), lines.end(), back_inserter(coords), parse_coords);

  priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
  for (size_t i = 0; i < coords.size() - 1; ++i) {
    for (size_t j = i + 1; j < coords.size(); ++j) {
      int dx = coords[i][0] - coords[j][0];
      int dy = coords[i][1] - coords[j][1];
      int dz = coords[i][2] - coords[j][2];
      long dist = 1L * dx * dx + 1L * dy * dy + 1L * dz * dz;
      pq.push({dist, {i, j}});
    }
  }

  UnionFind elements(coords.size());
  int last_u = -1, last_v = -1;
  while (!pq.empty()) {
    auto [dist, nodes] = pq.top();
    auto [u, v] = nodes;
    int root_u = elements.find(u);
    int root_v = elements.find(v);
    pq.pop();
    // only update the pair if we connect the pair
    if (root_u != root_v) {
      last_u = u;
      last_v = v;
      elements.unite(root_u, root_v);
    }
  }

  return 1L * coords[last_u][0] * coords[last_v][0];
}

int main() {
  string file_name = "input8.txt";
  // cout << "Part 1 result is " << part_1(file_name) << endl;
  cout << "Part 2 result is " << part_2(file_name) << endl;
}
