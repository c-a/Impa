#include <cstdio>
#include <cstdint>
#include <queue>

using namespace std;

struct City {
  int size;
  int b;
  int max;

  void SetB(int nb) {
    b = nb;
    max = (size + b - 1) / b;
  }
  bool operator<(const City& other) const {
    return max < other.max;
  }
};

int main() {
  int N, B;
  vector<int> sizes;
  while (scanf("%d %d", &N, &B) == 2) {
    if (N == -1 || B == -1) break;
    sizes.resize(N);
    uint64_t sum = 0;
    for (int i = 0; i < N; ++i) {
      scanf("%d", &sizes[i]);
      sum += sizes[i];
    };
    int min = (sum + (B - 1)) / (B - N);
    priority_queue<City> cities;
    for (int i = 0; i < N; i++) {
      City c;
      c.size = sizes[i];
      c.SetB(std::max(1, c.size / min));
      B -= c.b;
      cities.push(c);
    }
    while (B-- > 0) {
      City c = cities.top(); cities.pop();
      c.SetB(c.b + 1);
      cities.push(c);
    }
    const City& c = cities.top();
    printf("%d\n", c.max);
  }
}

