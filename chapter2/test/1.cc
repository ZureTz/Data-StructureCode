#include <cstddef>
#include <iostream>
#include <list>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t nElements1;
  cin >> nElements1;
  std::list<int> l1(nElements1);
  for (auto &node : l1) {
    cin >> node;
  }

  size_t nElements2;
  cin >> nElements2;
  std::list<int> l2(nElements2);
  for (auto &node : l2) {
    cin >> node;
  }

  int count = 0;
  std::list<int> tempList;
  for (auto it = l1.begin(); it != l1.end(); ++it) {
    for (auto it_2 = l2.begin(); it_2 != l2.end(); ++it_2) {
      if (*it == *it_2) {
        tempList.push_back(*it);
        count++;
        break;
      }
    }
  }

  if (count == 0) {
    cout << count << "\n没有公共元素" << std::endl;
    return 0;
  }

  cout << count << std::endl;
  for (const int num : tempList) {
    cout << num << ' ';
  }
  cout << std::endl;

  return 0;
}