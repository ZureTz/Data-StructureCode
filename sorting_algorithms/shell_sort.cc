#include <iostream>
#include <vector>
#include <utility>
using std::cout;

template <typename T>
void insertionGapSort(std::vector<T> &array, int begin, int gap) {
  for (int i = begin + gap; i < array.size(); i += gap) {
    for (int j = i; j > 0 && array[j - gap] > array[j]; j -= gap) {
      std::swap(array[j], array[j - gap]);
    }
  }
}

template <typename T> void shellSort(std::vector<T> &array) {
  int gap = array.size() / 2;
  while (gap) {
    for (int i = 0; i < gap; ++i) {
      insertionGapSort(array, i, gap);
    }
    gap /= 2;
  }
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::vector<int> arr{
      2, 3, 1,  3,  6,  9,  3,  6,  5,  3,  3, -12, 3, -6, 5, 3, 6,  5, 3,
      5, 3, 16, 25, 13, 67, 56, 3,  10, 3,  6, 7,   3, 6,  5, 3, 6,  5, 3,
      6, 5, 23, 6,  3,  32, 36, 35, 3,  67, 5, 3,   6, 1,  2, 4, 34, 5,
  };
  shellSort(arr);
  for (const int num  : arr) {
    cout << num << ' ';
  }


  return 0;
}