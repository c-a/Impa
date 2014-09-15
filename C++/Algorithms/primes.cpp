#include <vector>
#include <algorithm>
#include <cassert>

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
  Primes p(1000);
  assert(!p.IsPrime(0));
  assert(!p.IsPrime(1));
  assert(p.IsPrime(2));
  assert(p.IsPrime(3));
  assert(!p.IsPrime(4));
  assert(p.IsPrime(991));
  assert(p.IsPrime(997));
  assert(!p.IsPrime(998));
  assert(!p.IsPrime(999));
  assert(!p.IsPrime(1000));

  assert(p.primes().front() == 2);
  assert(p.primes().back() == 997);
}