#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

void except(std::string &dest, std::vector<int> &pos, const std::string &s,
            const std::string &t) {
  dest.clear();
  dest.reserve(s.size());
  pos.clear();
  pos.reserve(s.size());

  const std::unordered_set<char> charInT(t.begin(), t.end());
  std::unordered_set<char> checkDuplicate;
  for (int i = 0; i < s.length(); i++) {
    if (checkDuplicate.find(s[i]) != checkDuplicate.end()) {
      continue;
    }
    if (charInT.find(s[i]) != charInT.end()) {
      continue;
    }
    dest.push_back(s[i]);
    pos.push_back(i);
    checkDuplicate.insert(s[i]);
  }
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string s("cccabbccccdefgfff");
  std::string t("gedfa");
  std::string r;
  std::vector<int> pos;
  except(r, pos, s, t);

  std::cout << r << '\n';
  for (const int num : pos) {
    std::cout << num;
  }
  std::cout << std::endl;
  for (const int num : pos) {
    std::cout << s[num];
  }
  std::cout << std::endl;

  return 0;
}