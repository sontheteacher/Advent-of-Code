#include "helper.h"

using namespace std;
typedef vector<string> vs;
typedef long long ll;

int line_joltage(string &line) {
  int max_joltage = 0;
  int max_digit_so_far = line[0] - '0';
  for (size_t i = 1; i < line.size(); ++i) {
    int current_digit = line[i] - '0';

    // 1. Calculate joltage using the best digit found PRIOR to this one
    int current_joltage = (max_digit_so_far * 10) + current_digit;

    // 2. Keep track of the highest joltage overall
    if (current_joltage > max_joltage) {
      max_joltage = current_joltage;
    }

    // 3. Update the best possible tens digit for the NEXT batteries
    if (current_digit > max_digit_so_far) {
      max_digit_so_far = current_digit;
    }
  }
  return max_joltage;
}

ll line_joltage_12(string &line) {
  int n = line.size();
  int k = 12;

  string res;
  int to_remove = n - k;
  for (int i = 0; i < n; ++i) {
    // pop if we can improve the result (current > back)
    // and we have enough future digits

    while (!res.empty() && res.back() < line[i] && to_remove > 0) {
      res.pop_back();
      to_remove--;
    }
    res.push_back(line[i]);
  }
  res.resize(k);
  return stoll(res);
}

long part1(vs &input) {
  long result = 0;
  for (auto line : input) {
    result += line_joltage(line);
  }
  return result;
}

ll part2(vs &input) {
  ll result = 0;
  for (auto line : input) {
    result += line_joltage_12(line);
  }
  return result;
}

int main() {
  vs input = read_input("input3.txt");
  // cout << "Part 1 result is " << part1(input) << endl;
  cout << "Part 2 result is " << part2(input) << endl;
}
