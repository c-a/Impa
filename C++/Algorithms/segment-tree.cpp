#include <cassert>
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

int main() {
  std::vector<int> v{0, 1, 2};
  SegmentTree<int> st(v);

  assert(st.rmq(0, 0) == 0);
  assert(st.rmq(0, 1) == 1);
  assert(st.rmq(1, 2) == 3);
  assert(st.rmq(0, 2) == 3);

  st.update(0, 4);
  assert(st.rmq(0, 0) == 4);
  assert(st.rmq(0, 1) == 5);
  assert(st.rmq(1, 2) == 3);
  assert(st.rmq(0, 2) == 7);
}