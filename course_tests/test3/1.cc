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
  for (auto &str : strs) {
    std::getline(std::cin, str);
  }

  if (mode == 1) {

    for (const auto &str : strs) {
      if (str.find(toFind) == std::string::npos) {
        continue;
      }
      cout << str << std::endl;
    }

    return 0;
  }

  std::string tofindLower = toFind;
  std::vector<std::string> lowerStrs = strs;

  for (auto &ch : tofindLower) {
    ch = tolower(ch);
  }

  for (auto & str : lowerStrs) {
    for (auto &ch : str) {
      ch = tolower(ch);
    }
  }

  for (int i = 0; i < lowerStrs.size(); ++i) {
    if (lowerStrs[i].find(tofindLower) == std::string::npos) {
      continue;
    }
    cout << strs[i] << std::endl;
  }

  return 0;
}