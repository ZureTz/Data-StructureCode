#include <algorithm>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t nSize;
  cin >> nSize;
  std::vector<int> arr;
  arr.reserve(nSize);
  {
    int temp;
    for (size_t i = 0; i < nSize; ++i) {
      cin >> temp;
      if (temp <= 0) {
        continue;
      }
      arr.push_back(temp);
    }
  }
  std::sort(arr.begin(), arr.end());
  // for (const int num : arr) {
  //   cout << num << ' ';
  // }
  // cout << std::endl;

  int min = 1;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    if (*it == min) {
      ++min;
      continue;
    }
    if (*it > min) {
      break;
    }
  }

  cout << min;

  return 0;
}