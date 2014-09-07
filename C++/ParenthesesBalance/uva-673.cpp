#include <vector>
#include <string>
#include <iostream>

bool Correct(const std::string& line) {
  std::vector<char> stack;
  for (char c : line) {
    if (c == '(' || c == '[') {
      stack.push_back(c);
    } else if (c == ')' || c == ']') {
      if (stack.empty()) return false;
      char back = stack.back();
      if (c == ')' && back != '(') return false;
      if (c == ']' && back != '[') return false;
      stack.pop_back();
    } else {
      return false;
    }
  }
  return stack.empty();
}

int main() {
  int n;
  std::cin >> n;
  std::string line;
  std::getline(std::cin, line);
  while (n-- > 0) {
    std::getline(std::cin, line);
    std::cout << (Correct(line) ? "Yes\n" : "No\n");
  }
  return 0;
}

