#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

int index(char c) {
  int i = c - 'a';
  if (c > 'q') --i;
  return i;
}

char character(int i) {
  char c = 'A' + i;
  if (c >= 'Q') ++c;
  return c;
}

int main() {
  int N;
  cin >> N;
  cin.ignore(100, '\n');
  while (--N >= 0) {
    string key;
    getline(cin, key);
    vector<bool> A(25, false);
    vector<int> row(25, 0), col(25, 0);
    char T[5][5];
    int r = 0, c = 0;
    for (char k : key) {
      if (k == ' ') continue;
      int i = index(k);
      if (A[i]) continue;
      row[i] = r; col[i] = c;
      T[r][c] = i;
      if ((c = (c + 1) % 5) == 0) ++r;
      A[i] = true;
    }
    for (int i = 0; i < 25; ++i) {
      if (A[i]) continue;
      row[i] = r; col[i] = c;
      T[r][c] = i;
      if ((c = (c + 1) % 5) == 0) ++r;
      A[i] = true;
    }

    string plain;
    getline(cin, plain);
    plain.erase(std::remove(plain.begin(), plain.end(), ' '), plain.end());
    string out;
    out.reserve(plain.size());
    for (int i = 0; i < plain.size();) {
      int i1 = index(plain[i]);
      ++i;
      int i2;
      if (i < plain.size() && index(plain[i]) != i1){
        i2 = index(plain[i]);
        ++i;
      } else {
        i2 = index('x');
      }
      int o1, o2;
      if (row[i1] == row[i2]) {
        o1 = T[row[i1]][(col[i1] + 1) % 5];
        o2 = T[row[i2]][(col[i2] + 1) % 5];
      } else if (col[i1] == col[i2]) {
        o1 = T[(row[i1] + 1) % 5][col[i1]];
        o2 = T[(row[i2] + 1) % 5][col[i2]];
      } else {
        o1 = T[row[i1]][col[i2]];
        o2 = T[row[i2]][col[i1]];
      }
      out.push_back(character(o1)); out.push_back(character(o2));
    }
    cout << out << "\n";
  }
}
