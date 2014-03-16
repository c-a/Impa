#include <algorithm>
#include <array>
#include <cstdio>

template<typename base_t, typename expo_t>
constexpr base_t POW(base_t base, expo_t expo)
{
    return (expo != 0 ) ? base * POW(base, expo -1) : 1;
}

template<int PILES, int CANDIES>
class FreeCandies {
 public:
  int get_max(const std::array< std::array<int, CANDIES>, PILES >& piles,
              std::array<int, PILES> piles_pos) {
    piles_ = piles;
    dp_.fill(-1);
    std::array<int, 5> basket;
    basket.fill(-1);
    return run(piles_pos, basket, 0);
  }

 private:
  int run(std::array<int, PILES>& pile_heights, std::array<int, 5>& basket,
          int curr) {
    int& res = dp_[calc_dp_index(pile_heights)];
    if (res != -1)
      return res;

    res = curr;

    // Check if the basket is full.
    auto free_pos = std::find(basket.begin(), basket.end(), -1);
    if (free_pos == basket.end())
      return res;

    // Try which pile it's best to take a candy from.
    for (int i = 0; i < PILES; ++i) {
      if (pile_heights[i] > 0) {
        int candy = piles_[i][pile_heights[i] - 1];
        auto candy_pos = std::find(basket.begin(), basket.end(), candy);
        if (candy_pos != basket.end()) {
          pile_heights[i] -= 1;
          *candy_pos = -1;
          res = std::max(res, run(pile_heights, basket, curr+1));
          *candy_pos = candy;
          pile_heights[i] += 1;
        } else {
          pile_heights[i] -= 1;
          *free_pos = candy;
          res = std::max(res, run(pile_heights, basket, curr));
          *free_pos = -1;
          pile_heights[i] += 1;
        }
      }
    }
    return res;
  }

  static int calc_dp_index(const std::array<int, PILES>& pos) {
    int index = 0;
    for (int pile_pos : pos) {
      index = index*CANDIES + pile_pos;
    }
    return index;
  }

  std::array< std::array<int, CANDIES>, PILES > piles_;
  std::array<int, POW(CANDIES, PILES + 1)> dp_;
};

int main() {
  FreeCandies<4, 40>* fc = new FreeCandies<4, 40>();

  int n;
  while (scanf("%d", &n) == 1) {
    if (n == 0) break;

    std::array< std::array<int, 40>, 4 > piles;
    for (int i = n - 1; i >= 0; --i) {
      scanf("%d %d %d %d", &piles[0][i], &piles[1][i], &piles[2][i], &piles[3][i]);
    }
    std::array<int, 4> piles_pos;
    piles_pos.fill(n);
    printf("%d\n", fc->get_max(piles, piles_pos));
  }
}
