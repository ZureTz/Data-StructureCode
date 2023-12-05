#include <cstddef>
#include <functional>
#include <iostream>
#include <istream>
#include <unordered_map>
#include <utility>
struct pairHash {
  std::size_t operator()(const std::pair<int, int> &pair) const {
    return std::hash<int>()(pair.first) ^ (std::hash<int>()(pair.second) << 1);
  }
};

void input(std::istream &is,
           std::unordered_map<std::pair<int, int>, int, pairHash> &mat,
           int nElements) {
  while (nElements-- > 0) {
    int i, j, num;
    is >> i >> j >> num;
    mat[{i - 1, j - 1}] = num;
  }
}

int main(int argc, char const *argv[]) {

  std::unordered_map<std::pair<int, int>, int, pairHash> mat1;
  int m1m, m1n, m1j;
  std::cin >> m1m >> m1n >> m1j;
  input(std::cin, mat1, m1j);

  std::unordered_map<std::pair<int, int>, int, pairHash> mat2;
  int m2m, m2n, m2j;
  std::cin >> m2m >> m2n >> m2j;
  input(std::cin, mat2, m2j);

  if (!((m1m == m2m) and (m1n == m2n))) {
    std::cout << "FALSE" << std::endl;
    return 0;
  }

  for (int i = 0; i < m1m; ++i) {
    for (int j = 0; j < m1n; ++j) {
      int result = 0;
      auto mat1Find = mat1.find({i, j});
      result += (mat1Find != mat1.end()) ? mat1Find->second : 0;
      std::cout << result << ' ';
    }
    std::cout.put('\n');
  }

  for (int i = 0; i < m1m; ++i) {
    for (int j = 0; j < m1n; ++j) {
      int result = 0;
      auto mat2Find = mat2.find({i, j});
      result += (mat2Find != mat2.end()) ? mat2Find->second : 0;
      std::cout << result << ' ';
    }
    std::cout.put('\n');
  }

  for (int i = 0; i < m1m; ++i) {
    for (int j = 0; j < m1n; ++j) {
      int result = 0;

      auto mat1Find = mat1.find({i, j});
      auto mat2Find = mat2.find({i, j});
      result += (mat1Find != mat1.end()) ? mat1Find->second : 0;
      result += (mat2Find != mat2.end()) ? mat2Find->second : 0;

      std::cout << result << ' ';
    }
    std::cout.put('\n');
  }

  return 0;
}