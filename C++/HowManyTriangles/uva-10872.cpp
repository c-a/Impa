#include <cstdio>
#include <cstdint>
#include <vector>

uint64_t div_round_closest(uint64_t a, uint32_t b) {
  return (a + b/2) / b;
}

int main() {
  for (int caseN = 1;; ++caseN) {
    uint64_t val;
    scanf("%lld", &val);
    if (val == 0) break;
    uint64_t res;
    if ((val & 0x1) == 0) {
      res = div_round_closest(val*val, 48);
    } else {
      res = div_round_closest((val+3)*(val+3), 48);
    }
    printf("Case %d: %lld\n", caseN, res);
  }
}
