#include "helper.h"
#include <cctype>
#include <numeric>
#include <queue>

using namespace std;
typedef vector<string> vs;
typedef long long ll;

int part_1(vs input) {
  int res = 0;
  int width = input.size(), length = input[0].size();
  queue<pair<int, int>> q;
  pair<int, int> start = {0, input[0].find_first_of('S')};
  q.push(start);
  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();
    // assume r, c is valid. we will only add valid positions later on
    if (r + 1 < width) {
      // beam keep going down
      char target = input[r + 1][c];
      if (target == '.') {
        input[r + 1][c] = '|';
        q.push({r + 1, c});
      } else if (target == '^') {
        res++;
        // check the left and right to see if it's valid and unvisited
        if (c - 1 >= 0 && input[r + 1][c - 1] == '.') {
          q.push({r + 1, c - 1});
        }
        if (c + 1 < length && input[r + 1][c + 1] == '.') {
          q.push({r + 1, c + 1});
        }
      }
    }
  }

  return res;
}

// NOTE: For each beam position visited, we want to keep track of how many path
// we have to get to that square and once we hit a splitter, each of the
// splitter neighbor got increment by that much

ll part_2(vs input) {
  int width = input.size(), length = input[0].size();
  vector<vector<long>> counter(width, vector(length, 0l));
  queue<pair<int, int>> q;
  pair<int, int> start = {0, input[0].find_first_of('S')};
  q.push(start);
  counter[start.first][start.second] = 1;
  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();
    // assume r, c is valid. we will only add valid positions later on
    if (r + 1 < width) {
      char target = input[r + 1][c];
      // beam keep going down
      if (target == '.') {
        counter[r + 1][c] += counter[r][c];
        input[r + 1][c] = '|';
        q.push({r + 1, c});
      } else if (target == '^') {
        // check the left and right to see if it's valid
        if (c - 1 >= 0) {
          if (input[r + 1][c - 1] == '.') { // only add if unvisited
            q.push({r + 1, c - 1});
            input[r + 1][c - 1] = '|'; // mark as visited
          }
          counter[r + 1][c - 1] += counter[r][c];
        }
        if (c + 1 < length) {
          if (input[r + 1][c + 1] == '.') {
            input[r + 1][c + 1] = '|';
            q.push({r + 1, c + 1});
          }
          counter[r + 1][c + 1] += counter[r][c];
        }
      } else if (target == '|')
        counter[r + 1][c] += counter[r][c];
    }
  }

  // for (const auto &row : counter) {
  //   for (const auto &val : row) {
  //     cout << val << " ";
  //   }
  //   cout << endl;
  // }

  auto last_row = counter.back();
  return reduce(last_row.begin(), last_row.end(), 0ll);
}

int main() {
  string filename = "input7.txt";
  vs input = read_input(filename);
  // cout << "Part 1 result is " << part_1(input) << endl;
  cout << "Parr 2 result is: " << part_2(input) << endl;
}
