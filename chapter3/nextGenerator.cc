#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
using std::cout;

void nextGenerator(std::vector<int> &dest, const std::string &str) {
  if (str.length() == 0) {
    dest.resize(0);
    return;
  }
  if (str.length() == 1) {
    dest.resize(1);
    dest[0] = 0;
    return;
  }

  dest.resize(str.size());
  std::fill(dest.begin(), dest.end(), 0);

  size_t i = 1;
  while (i < str.length()) {
    size_t j = 0;
    int count = 1;
    bool flag = (str[i] == str[j]);
    while (i < str.length() && (str[i] == str[j])) {
      dest[i] = count++;
      i++;
      j++;
    }
    if (flag) {
      continue;
    }
    i++;
  }
}

size_t strSearch(const std::string &toFind, const std::string &pattern) {
  std::vector<int> next;
  nextGenerator(next, pattern);
  size_t toFindIndex = 0;
  size_t patternIndex = 0;
  while (toFindIndex < toFind.length()) {
    cout << "Outer: " << toFindIndex << ' ' << patternIndex << std::endl;
    bool flag = (toFind[toFindIndex] == pattern[patternIndex]);
    size_t tempResultPos = toFindIndex;
    while (toFindIndex < toFind.length() && patternIndex < pattern.length() &&
           toFind[toFindIndex] == pattern[patternIndex]) {
      cout << "Inner: " << toFindIndex << ' ' << patternIndex << std::endl;
      toFindIndex++;
      patternIndex++;
    }
    if (patternIndex == pattern.length()) {
      return tempResultPos;
    }
    if (toFind[toFindIndex] != pattern[patternIndex]) {
      patternIndex = next[patternIndex];
    }
    if (flag) {
      continue;
    }
    toFindIndex++;
  }
  return std::string::npos;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  if (argc != 3) {
    return 0;
  }

  const std::string toFind(argv[1]);
  cout << toFind << '\n' << argv[2] << std::endl;
  size_t foundPos = strSearch(toFind, argv[2]);
  cout << (foundPos == std::string::npos ? "Not found."
                                         : toFind.substr(foundPos))
       << std::endl;

  std::vector<int> dest;
  nextGenerator(dest, argv[2]);
  cout.put('[');
  for (const int num : dest) {
    cout << num << ", ";
  }
  cout<<"\b\b]";
  return 0;
}