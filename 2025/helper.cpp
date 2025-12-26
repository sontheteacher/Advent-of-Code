#include "helper.h"
#include <sstream>

using namespace std;

vector<string> read_input(const string &file_name) {
  vector<string> lines;
  ifstream file(file_name);
  string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  } else
    cout << "can't open file " << file_name << endl;
  return lines;
}

vector<string> split(const string &line, char delimeter) {
  vector<string> tokens;
  string token;
  stringstream ss(line);
  while (getline(ss, token, delimeter)) {
    if (token.size() > 0)
      tokens.push_back(token);
  }
  return tokens;
}
