#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

void except(std::string &s, std::vector<int> &pos, const std::string &t) {
  pos.clear();
  pos.reserve(s.size());

  const std::unordered_set<char> charInT(t.begin(), t.end());
  std::unordered_set<char> checkDuplicate;

  int index(0), tmpIndex(0);
  while (index < s.length()) {
    if (checkDuplicate.find(s[index]) != checkDuplicate.end()) {
      s.erase(index, 1);
      tmpIndex++;
      continue;
    }
    if (charInT.find(s[index]) != charInT.end()) {
      s.erase(index, 1);
      tmpIndex++;
      continue;
    }
    checkDuplicate.insert(s[index]);
    index++;
    pos.push_back(tmpIndex);
    tmpIndex++;
  }
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string s("cccabbccccdefgfff");
  std::string temp(s);
  std::string t("fffcef");
  std::vector<int> pos;
  except(s, pos, t);

  std::cout << s << '\n';
  for (const int index : pos) {
    std::cout << index<< ' ';
  }
  std::cout << std::endl;
  for (const int index : pos) {
    std::cout << temp[index];
  }
  std::cout << std::endl;

  return 0;
}