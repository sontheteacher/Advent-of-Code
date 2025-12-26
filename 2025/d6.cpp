#include "helper.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <ranges>

using namespace std;
typedef long long ll;
typedef vector<string> vs;

template <typename T>
vector<vector<T>> transpose(const vector<vector<T>> &matrix) {
  cout << "Running transpose " << endl;
  if (matrix.empty())
    return {};
  int n = matrix.size(), m = matrix[0].size();

  vector<vector<T>> result(m, vector<T>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      result[j][i] = matrix[i][j];
    }
  }
  cout << "Finished transpose " << endl;
  return result;
}

ll part1(const string &filename) {
  cout << "Running part1" << endl;
  vs input = read_input(filename);
  vector<vector<string>> matrix;
  for (auto row : input) {
    vs s_row = split(row, ' ');
    matrix.push_back(s_row);
  }
  ll res = 0;

  // NOTE: Assume each column has the same length
  auto inputT = transpose(matrix);
  for (auto row : inputT) {
    if (row.size() == 0)
      break;
    // NOTE: Convert the row to numbers except last one and insert into row_int
    vector<int> row_int;
    transform(row.begin(), row.end() - 1, back_inserter(row_int),
              [](const string &s) { return stol(s); });
    if (row.back() == "+") // width because we transposed
      res += reduce(row_int.begin(), row_int.end(), 0ll);
    else
      res +=
          reduce(row_int.begin(), row_int.end(), 1ll, std::multiplies<long>());
  }
  return res;
}

// NOTE: Read input but preserve the space in part 2
// and calculate directly from the input

ll part2(const string &filename) {
  vs input = read_input(filename);
  ll res = 0;

  // NOTE: Note that the distance between the signs on the last row
  // dictates the longest number of the current column

  int n_rows = input.size() - 1; // number of rows with numbers

  string ops_list = input.back();
  string ops = "+*";
  size_t curr = 0;

  // curr + 1 since curr is the current sign
  size_t next_pos = ops_list.find_first_of(ops, curr + 1);
  if (next_pos == string::npos)
    next_pos = ops_list.size() + 1;

  do {
    {
      auto dist = next_pos - curr - 1;
      vector<int> num_list;
      for (int i : std::views::iota(size_t(0), dist)) {
        string cur_num = "";
        for (int r : std::views::iota(0, n_rows)) {
          if (input[r][curr + i] != ' ')
            cur_num = cur_num + input[r][curr + i];
        }
        num_list.push_back(stoi(cur_num));
      }

      if (input[n_rows][curr] == '+')
        res += reduce(num_list.begin(), num_list.end(), 0ll);
      else
        res += reduce(num_list.begin(), num_list.end(), 1ll,
                      std::multiplies<long>());

      curr = next_pos;
      next_pos = ops_list.find_first_of(ops, curr + 1);
    }
  } while (next_pos != string::npos);

  // NOTE: For last column

  next_pos = ops_list.size();
  cout << "Curr pos is " << curr << endl;
  cout << "Next pos is " << next_pos << endl;

  auto dist = next_pos - curr;
  vector<int> num_list;
  for (int i : std::views::iota(size_t(0), dist)) {
    string cur_num = "";
    for (int r : std::views::iota(0, n_rows)) {
      if (input[r][curr + i] != ' ')
        cur_num = cur_num + input[r][curr + i];
    }
    cout << cur_num << endl;
    num_list.push_back(stoi(cur_num));
  }

  if (input[n_rows][curr] == '+')
    res += reduce(num_list.begin(), num_list.end(), 0ll);
  else
    res += reduce(num_list.begin(), num_list.end(), 1ll, std::multiplies<ll>());

  return res;
}

int main() {
  string filename = "input6.txt";
  // string filename = "input6_sample.txt";
  // cout << "Part 1 result is " << part1(filename) << endl;
  cout << "Part 2 result is " << part2(filename) << endl;
}
