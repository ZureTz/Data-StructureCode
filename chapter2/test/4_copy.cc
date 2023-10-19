#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(2 * n);
  for (auto &num : a) {
    cin >> num;
  }
  sort(a.begin(), a.end());
  cout << a.at(n - 1) << endl;

  return 0;
}