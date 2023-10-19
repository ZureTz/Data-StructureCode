#include <iostream>
#include <list>
using namespace std;

int main() {

  int n1, n2;
  cin >> n1;
  list<int> l1;
  for (int i = 0; i < n1; ++i) {
    int temp;
    cin >> temp;
    l1.push_back(temp);
  }
  cin >> n2;
  list<int> l2;
  for (int i = 0; i < n2; ++i) {
    int temp;
    cin >> temp;
    l2.push_back(temp);
  }
  int count = 0;

  list<int> tempList;
  for (auto i = l1.begin(); i != l1.end(); ++i) {
    for (const auto num : l2) {
      if (*i == num) {
        tempList.push_back(*i);
        count++;
        break;
      }
    }
  }

  if (count == 0) {
    cout << count << endl << "没有公共元素" << endl;
    return 0;
  } else {
    cout << count << endl;
    for (auto it = tempList.begin(); it != tempList.end(); ++it) {
      cout << *it << ' ';
    }
  }

  return 0;
}