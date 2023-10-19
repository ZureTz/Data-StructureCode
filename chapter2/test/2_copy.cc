#include <iostream>
#include <list>
using namespace std;

int main() {
  int n;
  cin >> n;
  list<int> l;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    l.push_back(t);
  }

  int x;
  cin >> x;
  auto i = l.begin();
  while (i != l.end()) {
    if (*i != x) {
      i++;
    } else {
      i = l.erase(i);
    }
  }

  for (int num : l) {
    cout << num << ' ';
  }

  return 0;
}