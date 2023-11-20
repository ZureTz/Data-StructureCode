#include <iostream>
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

template <typename T> void heapify(std::vector<T> &array, int size, int index) {
  int maxIndex = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  if (left < size && array[left] > array[maxIndex]) {
    maxIndex = left;
  }
  if (right < size && array[right] > array[maxIndex]) {
    maxIndex = right;
  }

  if (maxIndex != index) {
    std::swap(array[index], array[maxIndex]);
    heapify(array, size, maxIndex);
  }
}

template <typename T> void heapSort(std::vector<T> &array) {
  for (int i = array.size() / 2 - 1; i >= 0; --i) {
    heapify(array, array.size(), i);
  }

  for (int i = array.size() - 1; i >= 0; --i) {
    std::swap(array[0], array[i]);
    heapify(array, i, 0);
  }
}

int main(int argc, char const *argv[]) {
  std::vector<int> arr1{
      2, 3, 1,  3,  6,  9,  3,  6,  5,  3,  3, -12, 3, -6, 5, 3, 6,  5, 3,
      5, 3, 16, 25, 13, 67, 56, 3,  10, 3,  6, 7,   3, 6,  5, 3, 6,  5, 3,
      6, 5, 23, 6,  3,  32, 36, 35, 3,  67, 5, 3,   6, 1,  2, 4, 34, 5,
  };
  auto arr2 = arr1;

  heapSort(arr1);
  std::sort(arr2.begin(), arr2.end());
  cout << arr1 << arr2;
  return 0;
}