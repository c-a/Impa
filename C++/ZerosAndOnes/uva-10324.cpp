#include <iostream>
#include <string>
#include <vector>

#include <cstdlib>
#include <cstdio>
#include <cstring>

template<typename T>
class SegmentTree
{
public:
  SegmentTree(const std::vector<T>& a):
    n_(a.size())
  {
    st_.assign(4 * n_, T());
    build(a, 1, 0, n_ - 1);
  }

  T rmq(int i, int j) { return rmq(1, 0, n_ - 1, i, j); }
private:
  int n_;
  std::vector<T> st_;

  int left(int p) { return p << 1; }
  int right(int p) { return (p << 1) + 1; }

  void build(const std::vector<T>& a, int p, int l, int r) {
    if (l == r)
      st_[p] = a[l];
    else {
      int mid = l + (r - l) / 2;
      build(a, left(p), l, mid);
      build(a, right(p), mid + 1, r);

      st_[p] = st_[left(p)] + st_[right(p)];
    }
  }

  T rmq(int p, int l, int r, int i, int j) {
    if (i > r || j < l) return T(); // Outside of range
    if (l >= i && r <= j) return st_[p]; // Inside range

    int mid = l + (r - l) / 2;

    return rmq(left(p), l, mid, i, j) + rmq(right(p), mid + 1, r, i, j);
  }
};

struct Value
{
  enum Type
  {
    NONE,
    ZERO,
    ONE,
    BOTH
  };

  Value(): type(NONE) {}
  Value(Type t): type(t) {}

  Type type;
};

static const Value
operator+(const Value& lhs, const Value& rhs) {
    Value::Type newType;
    if (lhs.type == Value::NONE)
      newType = rhs.type;
    else if (rhs.type == Value::NONE)
      newType = lhs.type;
    else if (lhs.type == rhs.type)
      newType = lhs.type;
    else
      newType = Value::BOTH;

    return Value(newType);
}

int main() {
  std::string line;

  for (int caseN = 1; std::getline(std::cin, line); caseN++) {
    if (line.empty())
      break;

    std::vector<Value> a;
    for (std::string::iterator i = line.begin(); i != line.end(); ++i) {
      if (*i == '0')
        a.push_back(Value(Value::ZERO));
      else
        a.push_back(Value(Value::ONE));
    }

    SegmentTree<Value> st(a);

    std::cout << "Case " << caseN << ":" << std::endl;

    int n;
    std::cin >> n;
    while (n-- > 0) {
      int i, j;
      Value v;
      
      std::cin >> i >> j;
      v = st.rmq(std::min(i, j), std::max(i, j));
      if (v.type != Value::BOTH)
        std::cout << "Yes" << std::endl;
      else
        std::cout << "No" << std::endl;

      std::getline(std::cin, line);
    }
  }
  return 0;
}
