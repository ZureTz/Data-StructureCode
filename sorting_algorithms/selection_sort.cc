#include <__type_traits/is_swappable.h>
#include <iostream>
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

template <typename T> void selectionSort(std::vector<T> &array) {
  for (int i = 0; i < array.size() - 1; ++i) {
    int minimumIndex = i;
    for (int j = i; j < array.size(); ++j) {
      if (array[j] < array[minimumIndex]) {
        minimumIndex = j;
      }
    }
    if (array[i] != array[minimumIndex]) {
      std::swap(array[i], array[minimumIndex]);
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

  selectionSort(arr1);
  std::sort(arr2.begin(), arr2.end());
  cout << arr1 << arr2;
  return 0;
}