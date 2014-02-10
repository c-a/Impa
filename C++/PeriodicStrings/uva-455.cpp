#include <iostream>
#include <limits>

int main() {
  int N;

  std::cin >> N;
  while (--N >= 0) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;
    std::cin >> line;
    int period = 1;
    for (; period < line.size(); ++period) {
      if (line.size() % period != 0)
        continue;

      bool valid = true;
      for (size_t i = period; i < line.size(); i++) {
        if (line[i] != line[i % period]) {
          valid = false;
          break;
        }
      }

      if (valid)
        break;
    }

    std::cout << period << std::endl;
    if (N > 0)
      std::cout << std::endl;
  }
  return 0;
}
