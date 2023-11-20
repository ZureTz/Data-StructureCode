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

template <typename T>
void quickSort(std::vector<T> &array, int begin, int end) {
  if (begin >= end - 1) {
    return;
  }

  const T pivot = array[begin];
  int left = begin, right = end;
  while (left < right) {
    while (array[left] < pivot) {
      left++;
    }
    do {
      right--;
    }while (array[right] > pivot);
    if (left < right) {
      std::swap(array[left], array[right]);
    }
  }
  quickSort(array, begin, right + 1);
  quickSort(array, right + 1, end);
}

int main(int argc, char const *argv[]) {
  std::vector<int> arr1{
      2, 3, 1,  3,  6,  9,  3,  6,  5,  3,  3, -12, 3, -6, 5, 3, 6,  5, 3,
      5, 3, 16, 25, 13, 67, 56, 3,  10, 3,  6, 7,   3, 6,  5, 3, 6,  5, 3,
      6, 5, 23, 6,  3,  32, 36, 35, 3,  67, 5, 3,   6, 1,  2, 4, 34, 5,
  };
  auto arr2 = arr1;

  quickSort(arr1, 0, arr1.size());
  std::sort(arr2.begin(), arr2.end());
  cout << arr1 << arr2;
  return 0;
}