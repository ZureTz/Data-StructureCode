#include <__type_traits/is_swappable.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;

template <typename T> inline bool less(const T &a, const T &b) { return a < b; }
template <typename T> inline bool greater(const T &a, const T &b) {
  return a > b;
}

template <typename iterator, typename compare>
void qsort(iterator begin, iterator end, compare cmp) {
  if (begin >= end - 1) {
    return;
  }
  
  iterator middle = (begin + (end - 1 - begin) / 2);
  iterator left = begin, right = end;
  while (left < right) {
    while (cmp(*left, *middle)) {
      left++;
    }
    do {
      right--;
    } while (cmp(*middle, *right));
    if (left < right) {
      if (left == middle) {
        middle = right;
      } else if (right == middle) {
        middle = left;
      }
      std::swap(*left, *right);
    }
    // cout << middle - begin << ' ' << *middle << ' ' << std::endl;
    // for (auto it = begin; it != end; ++it) {
    //   cout << std::setw(3) << std::setfill(' ') << *it;
    // }
    // cout << std::endl;
  }
  // cout << std::endl;

  qsort(begin, right + 1, cmp);
  qsort(right + 1, end, cmp);
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::vector<int> arr{
      2, 3, 1,  3,  6,  9,  3,  6,  5,  3,  3, -12, 3, -6, 5, 3, 6,  5, 3,
      5, 3, 16, 25, 13, 67, 56, 3,  10, 3,  6, 7,   3, 6,  5, 3, 6,  5, 3,
      6, 5, 23, 6,  3,  32, 36, 35, 3,  67, 5, 3,   6, 1,  2, 4, 34, 5,
  };
  qsort(arr.begin(), arr.end(), less<int>);
  for (const int num : arr) {
    cout << num << ' ';
  }
  cout << std::endl;
  qsort(arr.begin(), arr.end(), greater<int>);
  for (const int num : arr) {
    cout << num << ' ';
  }
  cout << std::endl;

  return 0;
}