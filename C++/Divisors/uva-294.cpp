
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
    int64_t L, U;
    std::cin >> L >> U;

    int max_divisors = -1;
    int64_t best;
    for (int64_t P = L; P <= U; ++P) {
      int divisors = 1;
      if (P > 1) {
        std::vector<int64_t> factors = factorize(P, primes);
        std::vector<int> factor_counts;
        int count = 1;
        for (int i = 1; i < factors.size(); ++i) {
          if (factors[i] != factors[i-1]) {
            factor_counts.push_back(count);
            count = 1;
          } else {
            count += 1;
          }
        }
        factor_counts.push_back(count);

        for (int c : factor_counts) {
          divisors *= (c+1);
        }
      }
      if (divisors > max_divisors) {
        max_divisors = divisors;
        best = P;
      }
    }

    std::cout << "Between " << L << " and " << U << ", " << best
              << " has a maximum of " << max_divisors << " divisors.\n";
  }
}
