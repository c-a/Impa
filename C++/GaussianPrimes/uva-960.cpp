
#include <cstdint>
#include <iostream>
#include <vector>

std::vector<int32_t> gen_primes(int32_t max) {
  std::vector<bool> bits(max, true);
  std::vector<int32_t> primes;
  for (int32_t p = 2; p <= max;) {
    primes.push_back(p);
    // Cross out all multiples of p.
    for (int32_t i = 2*p; i <= max; i += p) {
      bits[i] = false;
    }
    // Find next prime.
    for (++p; p <= max; ++p) {
      if (bits[p]) break;
    }
  }
  return primes;
}

std::vector<int64_t> factorize(int64_t val, const std::vector<int32_t>& primes) {
  std::vector<int64_t> factors;
  for (const int32_t p : primes) {
    if (p > val*val) break;
    for (; val % p == 0; val /= p) factors.push_back(p);
  }
  if (val != 1)
    factors.push_back(val);
  return factors;
}

int main() {
  std::vector<int32_t> primes = gen_primes(100000);
  int N;
  std::cin >> N;
  while (--N >= 0) {
    int64_t a, b;
    std::cin >> a >> b;
    std::vector<int64_t> norm_factors = factorize(a*a + b*b, primes);
    int factors = 0;
    for (int i = 0; i < norm_factors.size(); ++i) {
      factors++;
      if (norm_factors[i] % 4 == 3) ++i;
    }
    std::cout << (factors > 1 ? "C" : "P") << "\n";
  }
}
