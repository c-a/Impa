#include <iostream>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <tuple>

using namespace std;

class Catan {
 private:
  struct Pos {
    int q, r;
    Pos operator+(const Pos& rhs) const {
      return {q + rhs.q, r + rhs.r};
    }
    void operator+=(const Pos& rhs) {
      q += rhs.q;
      r += rhs.r;
    }
    bool operator<(const Pos& rhs) const {
      return make_tuple(q, r) < make_tuple(rhs.q, rhs.r);
    }
  };
  enum Direction {
    N = 0, NW, SW, S, SE, NE, LENGTH
  };

 public:
  Catan(int N) {
    index_type_.reserve(N);
    Add({0, 0}, 0);
    
    Pos pos = {0, 0};
    int side = 1;
    while (index_type_.size() < N) {
      pos += dirs_[NE];
      Add(pos, GetType(pos));
      for (const auto& dir : dirs_) {
        int c = &dir == &dirs_[0] ? side - 1 : side;
        for (int s = 0; s < c; ++s) {
          pos += dir;
          Add(pos, GetType(pos));
        }
      }
      side++;
    }
  }

  int GetTypeForIndex(int i) {
    return index_type_[i - 1] + 1;
  }

private:
  void Add(const Pos& p, int type) {
    int i = index_type_.size();
    index_type_.push_back(type);
    pos_index_[p] = i;
    counts_[type]++;
  }

  int GetType(const Pos& p) {
    bool types[5] = {true, true, true, true, true};
    for (const auto& dir : dirs_) {
      auto iter = pos_index_.find(p + dir);
      if (iter != pos_index_.end()) {
        types[index_type_[iter->second]] = false;
      }
    }
    int type = -1;
    int count;
    for (int t = 0; t < 5; ++t) {
      if (!types[t]) continue;
      if (type == -1 || counts_[t] < count) {
        type = t;
        count = counts_[t];
      }
    }
    return type;
  }

  std::array<Pos, LENGTH> dirs_ = {{
    {0, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {1, -1} 
  }};

  map<Pos, int> pos_index_;
  vector<int> index_type_;
  int counts_[5] = {0, 0, 0, 0, 0};
};

int main() {
  Catan cat(10000);
  int c;
  cin >> c;
  while (--c >= 0) {
    int i;
    cin >> i;
    cout << cat.GetTypeForIndex(i) << "\n";
  }
}
