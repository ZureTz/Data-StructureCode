#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using std::cout;

int main(int argc, char const *argv[]) {
  std::string toFind;
  std::getline(std::cin, toFind);

  int mode, nStrings;
  (std::cin >> mode >> nStrings).get();

  std::vector<std::string> strs(nStrings);
  if (mode == 1) {
    for (auto &str : strs) {
      std::getline(std::cin, str);
    }
  } else {
    for (auto &ch : toFind) {
      ch = tolower(ch);
    }
    for (auto &str : strs) {
      std::string temp;
      std::getline(std::cin, temp);
      for (auto &ch : temp) {
        ch = tolower(ch);
      }
      str = temp;
    }
  }

  for (const auto&str : strs) {
    if (str.find(toFind)==std::string::npos) {
      continue;
    }
    cout << str << std::endl;
  }

  return 0;
}