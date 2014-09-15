#include <cstdio>
#include <vector>
#include <algorithm>

class Primes {
 public:
  Primes(uint32_t max) :
    is_prime_(max + 1, true) {
      is_prime_[0] = is_prime_[1] = false;
      for (int x = 2; x <= max; ++x) {
        if (!is_prime_[x]) continue;
        primes_.push_back(x);
        for (int v = x*x; v <= max; v += x) is_prime_[v] = false;
      }
    }
  bool IsPrime(uint32_t x) { return is_prime_[x]; }
  const std::vector<uint32_t> primes() { return primes_; }
 private:
  std::vector<bool> is_prime_;
  std::vector<uint32_t> primes_;
};

int main() {
  Primes primes(1000000 - 2);
  const std::vector<uint32_t>& p = primes.primes();
  uint32_t n;
  while (scanf("%u", &n) == 1) {
    if (n == 0) break;
    auto l = p.begin();
    auto u = std::lower_bound(p.begin(), p.end(), n);
    while (l != u) {
      uint32_t sum = *l + *u;
      if (sum < n) ++l;
      else if (sum > n) --u;
      else break;
    }
    printf("%u = %u + %u\n", n, *l, *u);
  }
}

