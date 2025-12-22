#include "helper.h"
#include <queue>
#include <unordered_set>

using namespace std;
typedef vector<string> vs;

vector<pair<int, int>> neighbors(int i, int j, int width, int length) {
  vector<pair<int, int>> res;
  for (int r = i - 1; r < i + 2; ++r) {
    if (r < 0 || r >= width)
      continue;
    for (int c = j - 1; c < j + 2; ++c) {
      if (c < 0 || c >= length || (c == j && r == i))
        continue;
      res.push_back({r, c});
    }
  }
  return res;
}

int part1(vs input) {
  int width = input.size(), height = input[0].size();
  int res = 0;
  for (int r = 0; r < width; ++r) {
    for (int c = 0; c < height; ++c) {
      if (input[r][c] == '@') {
        vector<pair<int, int>> node_neighbors = neighbors(r, c, width, height);
        int c = 0;
        for (pair<int, int> pairs : node_neighbors) {
          auto [nr, nc] = pairs;
          if (input[nr][nc] == '@')
            c++;
        }
        if (c < 4)
          res++;
      }
    }
  }
  return res;
}

int part2(vs input) {
  int width = input.size(), length = input[0].size();
  vector<vector<int>> grid_count(width, vector<int>(length, 0));

  queue<pair<int, int>> q;

  // NOTE: First create a grid count of number of neighbor paper rolls
  // and initialize the BFS queue if grid < 4
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < length; ++j) {
      if (input[i][j] == '@') {
        for (auto pair : neighbors(i, j, width, length)) {
          auto [nr, nc] = pair;
          if (input[nr][nc] == '@')
            grid_count[i][j] += 1;
        }
      }
    }
  }

  // NOTE: Mark as visited the ones in the q
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < length; ++j) {
      if (input[i][j] == '@' && grid_count[i][j] < 4) {
        input[i][j] = '.';
        q.push({i, j});
      }
    }
  }
  int res = 0;

  // NOTE: Now do a all source bfs
  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();
    res++;
    for (auto pair : neighbors(r, c, width, length)) {
      auto [nr, nc] = pair;
      if (input[nr][nc] == '@') {
        grid_count[nr][nc]--;
        if (grid_count[nr][nc] < 4) {
          q.push({nr, nc});
          input[nr][nc] = '.';
        }
      }
    }
  }
  return res;
}

int main() {
  string file_name = "input4.txt";
  vs input = read_input(file_name);
  int p1 = part1(input);
  cout << "Part 1 result is " << p1 << endl;

  int p2 = part2(input);
  cout << "Part 2 result is " << p2 << endl;
}
