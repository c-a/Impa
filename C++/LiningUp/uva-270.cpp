#include <cstdio>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

struct Line {
  int num, den;
  int b;
  bool operator==(const Line& other) const {
    return num == other.num && den == other.den && b == other.b;
  }
};

namespace std {
  template<>
  struct hash<Line> {
    typedef Line argument_type;
    typedef size_t value_type;

    value_type operator()(const argument_type& l) const {
      size_t seed = 0;
      hash_combine(seed, l.num);
      hash_combine(seed, l.den);
      hash_combine(seed, l.b);
      return seed;
    }
  };
  template<>
  struct hash<pair<int, int>> {
    typedef pair<int, int> argument_type;
    typedef size_t value_type;

    value_type operator()(const argument_type& p) const {
      size_t seed = 0;
      hash_combine(seed, p.first);
      hash_combine(seed, p.second);
      return seed;
    }
  };
}

int gcd(int a, int b) {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}

int main() {
  int cases;
  cin >> cases;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vector<pair<int, int>> points;
  unordered_map<Line, unordered_set<pair<int, int>>> line_counts;
  line_counts.reserve(700*700);
  points.reserve(700);
  while (--cases >= 0) {
    points.clear();
    while (true) {
      string line;
      getline(cin, line);
      if (line.empty()) break;
      pair<int, int> point;
      sscanf(line.c_str(), "%d %d", &point.first, &point.second);
      points.push_back(point);
    }
    line_counts.clear();
    int m = 0;
    for (int i = 0; i < points.size(); ++i) {
      const pair<int, int>& p1 = points[i];
      for (int j = i + 1; j < points.size(); ++j) {
        const pair<int, int>& p2 = points[j];
        // Check if vertical
        if (p1.first == p2.first) {
          unordered_set<pair<int, int>>& lps = line_counts[{1, 0, p1.first}];
          lps.insert(p1); lps.insert(p2);
          m = std::max(m, static_cast<int>(lps.size()));
        } else {
          int num = p2.second - p1.second;
          int den = p2.first - p1.first;
          int d = gcd(num, den);
          num /= d; den /= d;
          int b = p1.second*den - p1.first*num;
          unordered_set<pair<int, int>>& lps = line_counts[{num, den, b}];
          lps.insert(p1); lps.insert(p2);
          m = std::max(m, static_cast<int>(lps.size()));
        }
      }
    }
    cout << m << endl;
    if (cases > 0)
      cout << endl;
  }
}
