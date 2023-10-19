#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <vector>
using std::array;
using std::cin;
using std::cout;
using std::vector;

struct Matrix {
  vector<int> datas;
  vector<vector<bool>> pos;
  Matrix(int m, int n) {
    pos.resize(m);
    for (auto &row : pos) {
      row.resize(n);
    }
  }
};

void add(Matrix &dest, const Matrix &m1, const Matrix &m2) {
  if (!(m1.pos.size() == m2.pos.size() &&
        m1.pos.front().size() == m2.pos.front().size())) {
    std::cerr << "Invalid size" << std::endl;
    exit(EXIT_FAILURE);
  }

  const int m = m1.pos.size();
  const int n = m1.pos.front().size();

  dest.datas.clear();
  dest.pos.resize(m);
  std::fill(dest.pos.begin(), dest.pos.end(), vector<bool>(n));

  auto m1It = m1.datas.begin(), m2It = m2.datas.begin();
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      int data1 = 0, data2 = 0;
      if (m1It < m1.datas.end() && m1.pos[i][j]) {
        data1 = *(m1It++);
      }
      if (m2It < m2.datas.end() && m2.pos[i][j]) {
        data2 = *(m2It++);
      }
      const int result = data1 + data2;
      if (result == 0) {
        continue;
      }
      dest.pos[i][j] = 1;
      dest.datas.push_back(result);
    }
  }
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  Matrix m1(3, 3), m2(3, 3);
  m1.datas = {2, 3, 5, 7};
  m1.pos = {
      {1, 0, 0},
      {0, 0, 1},
      {1, 0, 1},
  };
  m2.datas = {-22, 5, 3, 7};
  m2.pos = {
      {1, 0, 0},
      {0, 1, 0},
      {1, 0, 1},
  };

  Matrix res(3, 3);
  add(res, m1, m2);
  for (const int num : res.datas) {
    cout << num << ' ';
  }
  cout << std::endl;
  for (const auto &row : res.pos) {
    for (const bool num : row) {
      cout << num << ' ';
    }
    cout << std::endl;
  }

  return 0;
}