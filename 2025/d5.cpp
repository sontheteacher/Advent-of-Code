#include "helper.h"
#include <algorithm>

using namespace std;

pair<vector<pair<long, long>>, vector<long>> read_file(const string &filename) {
  vector<pair<long, long>> intervals;
  vector<long> nums;
  ifstream file(filename);
  string line;
  if (file.is_open()) {
    // NOTE: First read all the intervals
    while (getline(file, line) && !line.empty()) {
      vector<string> line_sp = split(line, '-');
      long first = stol(line_sp[0]), second = stol(line_sp[1]);
      intervals.push_back({first, second});
    }
    // NOTE: Now get all the numbers to check
    while (getline(file, line)) {
      nums.push_back(stol(line));
    }
  }
  file.close();
  return {intervals, nums};
}

int part1(vector<pair<long, long>> intervals, vector<long> nums) {
  int res = 0;
  for (long num : nums) {
    for (auto interval : intervals) {
      auto [first, second] = interval;
      if (first <= num && second >= num) {
        res++;
        break;
      }
    }
  }
  return res;
}

long long part2(vector<pair<long, long>> intervals, vector<long> nums) {
  long long res = 0;
  sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b) {
    if (a.first != b.first)
      return a.first < b.first; // sort by ascending order
    else
      return a.second < b.second;
  });

  vector<pair<long, long>> merged;
  for (auto interval : intervals) {
    // NOTE: if overlapping or merged empty then append
    if (merged.empty() || merged.back().second < interval.first)
      merged.push_back(interval);
    else
      merged.back().second = max(merged.back().second, interval.second);
  }

  for (auto interval : merged) {
    auto [left, right] = interval;
    res += right - left + 1;
  }
  return res;
}

int main() {
  string filename = "input5.txt";
  auto [intervals, nums] = read_file(filename);
  cout << "Part 1 result is " << part1(intervals, nums);
  cout << "Part 2 result is " << part2(intervals, nums);
}
