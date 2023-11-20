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
std::vector<T> merge(const std::vector<T> &arr1, const std::vector<T> &arr2) {
  std::vector<T> result;
  result.reserve(arr1.size() + arr2.size());

  auto it1 = arr1.begin(), it2 = arr2.begin();
  while (it1 != arr1.end() && it2 != arr2.end()) {
    if (*it1 < *it2) {
      result.emplace_back(*(it1++));
      continue;
    }
    if (*it1 > *it2) {
      result.emplace_back(*(it2++));
      continue;
    }
    result.emplace_back(*(it1++));
    result.emplace_back(*(it2++));
  }

  while (it1 != arr1.end()) {
    result.emplace_back(*(it1++));
  }
  while (it2 != arr2.end()) {
    result.emplace_back(*(it2++));
  }

  return result;
}

template <typename T> std::vector<T> mergeSortImpl(const std::vector<T> &arr) {
  if (arr.size() <= 1) {
    return arr;
  }
  const auto mid = arr.begin() + ((arr.end() - arr.begin()) / 2);
  const std::vector<T> left(arr.begin(), mid);
  const std::vector<T> right(mid, arr.end());
  return merge(mergeSortImpl(left), mergeSortImpl(right));
}

template <typename T> void mergeSort(std::vector<T> &arr) {
  arr = mergeSortImpl(arr);
}

int main(int argc, char const *argv[]) {
  std::vector<int> arr1{
      2, 3, 1,  3,  6,  9,  3,  6,  5,  3,  3, -12, 3, -6, 5, 3, 6,  5, 3,
      5, 3, 16, 25, 13, 67, 56, 3,  10, 3,  6, 7,   3, 6,  5, 3, 6,  5, 3,
      6, 5, 23, 6,  3,  32, 36, 35, 3,  67, 5, 3,   6, 1,  2, 4, 34, 5,
  };
  auto arr2 = arr1;

  mergeSort(arr1);
  std::sort(arr2.begin(), arr2.end());
  cout << arr1 << arr2;

  std::vector<int> arr3{51, 12, 55, 23, 49, 7, 60, 36, 72, 12};
  mergeSort(arr3);
  cout <<  arr3;

  return 0;
}