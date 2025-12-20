#include "helper.h"
#include <string>

using namespace std;
typedef vector<string> vs;

long part1(const string &input) {
  vector<string> pairs = split(input, ',');
  long result = 0;

  for (string pair : pairs) {
    vs pair_split = split(pair, '-');

    long left = stol(pair_split[0]);
    long right = stol(pair_split[1]);
    while (left <= right) {
      // if left length is odd, then get the
      // smallext next lenght number (this is only used for
      // first iteration since all later iteration guarantee left has even
      // length)
      if (pair_split[0].size() % 2) {
        left = pow(10, long(log10(left) + 1));
        pair_split[0] = to_string(left);
      }
      // else grab the first half of the string representation of
      // left and see if double that would be in range.
      // then update left by taking the first half + 1
      else {
        string half = pair_split[0].substr(0, pair_split[0].size() / 2);
        string full = half + half;
        // cout << "candidate: " << full << endl;
        long candidate = stol(full);
        if (candidate >= left && candidate <= right)
          result += candidate;

        // update the left bound
        half = to_string(stol(half) + 1);
        pair_split[0] = half + half;
        left = stol(pair_split[0]);
      }
    }
  }
  return result;
}

long part2_helper(const vs &pairs, int n) {
  // NOTE: same as part 1, but generalized to n times
  long result = 0;

  for (string pair : pairs) {
    vs pair_split = split(pair, '-');
    cout << "left: " << pair_split[0] << " right: " << pair_split[1] << endl;

    long left = stol(pair_split[0]);
    long right = stol(pair_split[1]);
    while (left <= right) {
      // if left length is odd, then get the
      // smallext next lenght number (this is only used for
      // first iteration since all later iteration guarantee left has divisible
      // length length)
      int left_length = pair_split[0].size();
      // generalize for longer length number
      if (left_length % n) {
        left = pow(10, long(log10(left) + 1));
        pair_split[0] = to_string(left);
      }
      // else grab the length/n the string representation
      // and construct the candidate
      else {
        string small = pair_split[0].substr(0, pair_split[0].size() / n);
        string full = "";
        for (int i = 0; i < n; ++i)
          full += small;
        // cout << "candidate: " << full << endl;
        // harcoding the case length = 6, which might double count for n = 2 and
        // n = 3
        int mid = full.size() / 2;
        bool good = true;
        if (n == 3 && full.substr(0, mid) == full.substr(mid, full.size()))
          good = false;
        long candidate = stol(full);
        if (candidate >= left && candidate <= right && good) {
          cout << "candidate: " << full << endl;
          result += candidate;
        }

        // update the left bound
        small = to_string(stol(small) + 1);
        pair_split[0] = "";

        for (int i = 0; i < n; ++i)
          pair_split[0] += small;
        left = stol(pair_split[0]);
      }
    }
  }
  return result;
}

// TODO: similar to part 1, but the strign can be repeated n times.
// not just 2 times;
long part2(const string &input) {
  long result = 0;
  vs pairs = split(input, ',');
  vector<int> primes = {2, 3, 5, 7};
  // vector<int> primes = {2};
  for (int n : primes) {
    cout << "n is " << n << endl;
    result += part2_helper(pairs, n);
  }
  return result;
}

int main() {
  string filename = "input2.txt";
  string line = read_input(filename)[0];
  // long p1 = part1(line);
  // cout << "Part 1 answer is " << p1 << endl;
  long p2 = part2(line);
  cout << "Part 2 answer is " << p2 << endl;
}
