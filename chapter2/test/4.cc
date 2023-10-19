#include <iostream>
#include <iterator>
#include <list>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t nSize;
  cin >> nSize;
  // cout << nSize << std::endl;
  std::list<int> list1, list2;
  {
    int temp;
    for (size_t i = 0; i < nSize; ++i) {
      cin >> temp;
      list1.push_back(temp);
    }
    // for (const int num : list1) {
    //   cout << num << ' ';
    // }
    // cout << std::endl;

    for (size_t i = 0; i < nSize; ++i) {
      cin >> temp;
      list2.push_back(temp);
    }
    // for (const int num : list2) {
    //   cout << num << ' ';
    // }
    // cout << std::endl;
  }

  std::list<int> tempList;
  {
    auto it1 = list1.begin(), it2 = list2.begin();
    while (it1 != list1.end() && it2 != list2.end()) {
      if (*it1 < *it2) {
        tempList.push_back(*it1);
        ++it1;
        continue;
      }
      if (*it1 > *it2) {
        tempList.push_back(*it2);
        ++it2;
        continue;
      }
      tempList.push_back(*it1);
      tempList.push_back(*it1);
    }

    if (it1 == list1.end()) {
      tempList.splice(tempList.end(), list2, it2, list2.end());
    } else if (it2 == list2.end()) {
      tempList.splice(tempList.end(), list1, it1, list1.end());
    }
  }

  // for (const int num : tempList) {
  //   cout << num << ' ';
  // }
  // cout << std::endl;

  auto tIt = tempList.begin();
  std::advance(tIt, nSize - 1);
  cout << *tIt << std::endl;

  return 0;
}