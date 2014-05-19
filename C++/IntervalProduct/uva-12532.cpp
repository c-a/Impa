#include <cstdio>
#include <cmath>
#include <vector>

template<typename T>
class SegmentTree
{
public:
  SegmentTree(const std::vector<T>& a)
  : n_(1 << (size_t)(ceil(log2(a.size())))) {
    st_.assign(n_ << 1, T());
    build(a);
  }

  T rmq(int i, int j) { return rmq(0, 0, n_ - 1, i, j); }

  void update(int i, const T& val) {
    int p = (n_ - 1) + i;
    st_[p] = val;
    while (p != 0) {
      p = parent(p);
      st_[p] = st_[left(p)] + st_[right(p)];
    }
  }
private:
  int n_;
  std::vector<T> st_;

  int left(int p) { return (p << 1) + 1; }
  int right(int p) { return (p << 1) + 2; }
  int parent(int p) { return ((p-1) >> 1); }

  void build(const std::vector<T>& a) {
    int p = (n_ - 1);
    for (int i = 0; i < a.size(); ++i) {
      st_[p+i] = a[i];
    }
    init(0);
  }
  T init(int p) {
    if (p >= (n_ - 1)) {
      return st_[p];
    } else {
      return st_[p] = init(left(p)) + init(right(p));
    }
  }

  T rmq(int p, int l, int r, int i, int j) {
    if (i > r || j < l) return T(); // Outside of range
    if (l >= i && r <= j) return st_[p]; // Inside range

    int mid = l + (r - l) / 2;
    return rmq(left(p), l, mid, i, j) + rmq(right(p), mid + 1, r, i, j);
  }
};

struct Value {
  enum State {
    UNDEFINED,
    ZERO,
    POSITIVE,
    NEGATIVE
  } val;
  Value() : val(UNDEFINED) {}
  Value(State s) : val(s) {}
  Value operator+(const Value& rhs) {
    if (val == UNDEFINED) return rhs;
    if (rhs.val == UNDEFINED) return *this;
    if (val == ZERO || rhs.val == ZERO) return Value(ZERO);
    if (val == rhs.val) return Value(POSITIVE);
    return Value(NEGATIVE);
  }
};

Value GetValue(int val) {
  if (val < 0) return Value(Value::NEGATIVE);
  if (val > 0) return Value(Value::POSITIVE);
  return Value(Value::ZERO);
}

int main() {
  int N, K;
  while (scanf("%d %d", &N, &K) == 2) {
    std::vector<Value> values;
    for (int i = 0; i < N; ++i) {
      int val; scanf("%d", &val);
      values.push_back(GetValue(val));
    }
    SegmentTree<Value> st(values);
    for (int i = 0; i < K; ++i) {
      char c; int a, b;
      scanf(" %c %d %d", &c, &a, &b);
      if (c == 'C') {
        st.update(a-1, GetValue(b));
      } else {
        Value val = st.rmq(a-1, b-1);
        if (val.val == Value::ZERO)
          printf("0");
        else if (val.val == Value::POSITIVE)
          printf("+");
        else if (val.val == Value::NEGATIVE)
          printf("-");
        else
          printf("*");
      }
    }
    printf("\n");
  }
}
