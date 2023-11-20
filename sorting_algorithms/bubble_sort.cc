#include <algorithm>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
using std::cout;

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &array) {
  for (const int num : array) {
    os << num << ' ';
  }
  os.put('\n');

  return os;
}

template <typename T> void bubbleSort(std::vector<T> &array) {
  for (int i = 0; i < array.size() - 1; ++i) {
    bool swapped = false;
    for (int j = array.size() - 1; j > i; --j) {
      if (array[j - 1] > array[j]) {
        std::swap(array[j - 1], array[j]);
        swapped = true;
      }
    }
    if (swapped == false) {
      break;
    }
  }
}

int main(int argc, char const *argv[]) {
  std::vector<int> arr1{
      2, 3, 1,  3,  6,  9,  3,  6,  5,  3,  3, -12, 3, -6, 5, 3, 6,  5, 3,
      5, 3, 16, 25, 13, 67, 56, 3,  10, 3,  6, 7,   3, 6,  5, 3, 6,  5, 3,
      6, 5, 23, 6,  3,  32, 36, 35, 3,  67, 5, 3,   6, 1,  2, 4, 34, 5,
  };
  auto arr2 = arr1;

  bubbleSort(arr1);
  std::sort(arr2.begin(), arr2.end());
  cout << arr1 << arr2;

  return 0;
}