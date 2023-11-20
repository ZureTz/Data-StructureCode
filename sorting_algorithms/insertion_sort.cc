#include <__type_traits/is_swappable.h>
#include <iostream>
#include <vector>
using std::cout;

template <typename T> void insertionSort(std::vector<T> &array) {
  for (int i = 1; i < array.size(); ++i) {
    for (int j = i; j > 0 && array[j - 1] > array[j] ; --j) {
      std::swap(array[j], array[j - 1]);
    }
  }
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::vector<int> arr{
      2, 3, 1,  3,  6,  9,  3,  6,  5,  3,  3, -12, 3, -6, 5, 3, 6,  5, 3,
      5, 3, 16, 25, 13, 67, 56, 3,  10, 3,  6, 7,   3, 6,  5, 3, 6,  5, 3,
      6, 5, 23, 6,  3,  32, 36, 35, 3,  67, 5, 3,   6, 1,  2, 4, 34, 5,
  };
  insertionSort(arr);
  for (const int num : arr) {
    cout << num << ' ';
  }
  cout << std::endl;

  return 0;
}