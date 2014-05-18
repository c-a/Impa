#include <iostream>
#include <string>
#include <utility>
#include <cstring>
#include <vector>
#include <sstream>

static bool dp[256][256];

static bool
IsPalinword(const std::string& word) {
  if (word.size() <= 3) return false;
  
  for (int i = 0; i < word.size(); ++i)
    dp[i][i] = true;
  for (int i = 0; i <= word.size() - 2; ++i) {
      int j = i + 1;
      dp[i][j] = word[i] == word[j];
  }
  std::string candidate;
  int l, r;
  for (int size = 3; size < word.size(); ++size) {
    for (int i = 0; i <= word.size() - size; ++i) {
      int j = i + (size - 1);
      bool is_pal = dp[i+1][j-1] && word[i] == word[j];
      dp[i][j] = is_pal;
      if (is_pal) {
        std::string str = word.substr(i, size);
        if (candidate.empty()) {
          candidate = str;
          l = i; r = j;
        } else {
          if ((i > l || j < r) && str.find(candidate) == std::string::npos)
            return true;
        }
      }
    }
  }
  return false;
}

int main() {
  std::string line;
  while (std::cin >> line) {
    if (line.empty()) continue;
    std::stringstream ss(line);
    std::string word;
    while (std::getline(ss, word, ' ')) {
      if (IsPalinword(word))
        std::cout << word << std::endl;
    }
  }
  return 0;
}
