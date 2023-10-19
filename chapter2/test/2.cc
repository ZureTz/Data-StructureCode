#include <iostream>
#include <list>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t nElements;
  cin >> nElements;
  std::list<int> list(nElements);
  for (auto &num : list) {
    cin >> num;
  }

  int numToBeDel;
  cin >> numToBeDel;
  std::list<int>::iterator it = list.begin();
  while (it != list.end()) {
    if (*it != numToBeDel) {
      ++it;
      continue;
    }
    it = list.erase(it);
  }

  for (const int num : list) {
    cout << num << ' ';
  }

  return 0;
}