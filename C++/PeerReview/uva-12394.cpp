#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace::std;

int main() {
  vector<set<int>> reviewedBy;
  vector<bool> violation;
  map<int, string> institutionMap;
  while (true) {
    int K, N;
    std::cin >> K >> N;
    if (K == 0 || N == 0) break;
    reviewedBy.assign(N, set<int>());
    violation.assign(N, false);
    institutionMap.clear();
    for (int n = 0; n < N; ++n) {
      string institution;
      std::cin >> institution;
      institutionMap.emplace(n, institution);
      for (int k = 0; k < K; ++k) {
        int paper;
        std::cin >> paper;
        if (!reviewedBy[paper - 1].insert(n).second) {
          violation[paper - 1] = true;
        }
      }
    }
    for (int n = 0; n < N; ++n) {
      const set<int>& reviewers = reviewedBy[n];
      if (reviewers.size() != K) {
        violation[n] = true; continue;
      }
      const string& institution = institutionMap[n];
      for (const int reviewer : reviewers) {
        if (institutionMap[reviewer] == institution) {
          violation[n] = true;
          break;
        }
      }
    }

    int violations = std::count(
      violation.begin(), violation.end(), true);
    if (violations == 0) {
      std::cout << "NO PROBLEMS FOUND\n";
    }
    else if (violations == 1) {
      std::cout << "1 PROBLEM FOUND\n";
    } else {
      std::cout << violations << " PROBLEMS FOUND\n";
    }
  }
}

