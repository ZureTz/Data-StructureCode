#include <iostream>
#include <vector>
using std::cout;

template <typename T> int binarySearch(const std::vector<T> &arr, T val) {
  int low = 0, high = arr.size() - 1;
  while (low <= high) {
    const int mid = (low + high) / 2;
    if (val == arr[mid]) {
      return mid;
    }
    if (val < arr[mid]) {
      high = mid - 1;
    }
    if (val > arr[mid]) {
      low = mid + 1;
    }
  }
  return -1;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::vector<int> array{
      1, 2, 5, 7, 13, 15, 25, 27, 36,
  };
  int count = 0;
  for (const int num : array) {
    cout << count++ << ": " << num << '\n';
  }
  cout.put('\n');
  int index = binarySearch(array, 13);
  cout << index << ": " << (index >= 0 ? array[index] : 0) << '\n';
  index = binarySearch(array, 7);
  cout << index << ": " << (index >= 0 ? array[index] : 0) << '\n';
  index = binarySearch(array, 3);
  cout << index << ": " << (index >= 0 ? array[index] : 0) << '\n';


  return 0;
}