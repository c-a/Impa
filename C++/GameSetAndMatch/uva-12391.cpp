#include <cstdio>
#include <tuple>

class TennisProbability {
 public:
  std::tuple<double, double, double> Calculate(double p) {
    double winGameProb = WinByTwoProb(4, p, DeuceProb(p));
    double winTieBreakProb = WinByTwoProb(7, p, DeuceProb(p));
    double winSetProb = WinByTwoProb(6, winGameProb, winTieBreakProb);
    double winMatchProb = winSetProb*winSetProb +
        2 * winSetProb*winSetProb * (1 - winSetProb);
    return std::make_tuple(winGameProb, winSetProb, winMatchProb);
  }
 private:
  double WinByTwoProb(int min, double p, double deuceProb) {
    for (int i = 0; i <= min + 1; ++i) {
      for (int j = 0; j <= min + 1; ++j) {
        dp_[i][j] = -1.0;
      }
    }
    dp_[min][min] = deuceProb;
    dp_[min][min-1] = p + (1 - p) * deuceProb;
    dp_[min-1][min] = p * deuceProb;

    p_ = p;
    min_  = min;
    return Prob(0, 0);
  }

  double Prob(int i, int j) {
    if (dp_[i][j] != -1.0) return dp_[i][j];
    if (i >= min_ && i >= j + 2) return 1.0;
    if (j >= min_ && j >= i + 2) return 0.0;

    dp_[i][j] = p_ * Prob(i + 1, j) + (1 - p_) * Prob(i, j + 1);
    return dp_[i][j];
  }

  double DeuceProb(double p) {
    return p*p / (1 - 2*p*(1-p));
  }
  double dp_[9][9];
  double p_;
  double min_;
};

int main() {
  double p;
  TennisProbability tp;
  while (scanf("%lf", &p) == 1 && p != -1.0) {
    double game, set, match;
    std::tie(game, set, match) = tp.Calculate(p);
    printf("%.11lf %.11lf %.11lf\n", game, set, match);
  }
}
