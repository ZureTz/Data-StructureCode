#include <climits>
#include <cstddef>
#include <iostream>
#include <set>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>
using std::cin;
using std::cout;

// struct pairCmp {
//   bool operator()(const std::pair<int, int> &lhs,
//                   const std::pair<int, int> &rhs) {
//     return std::tie(lhs.first, lhs.second) < std::tie(rhs.first, rhs.second);
//   }
// };

void saddlePoints(std::vector<std::pair<int, int>> &dest,
                  const std::vector<std::vector<int>> &mat) {
  // for each row storing index(es) to the minimum values.
  std::vector<std::stack<int>> tempRowIndexs(mat.size());
  for (int i = 0; i < mat.size(); ++i) {
    int min = INT_MAX;
    for (int j = 0; j < mat[i].size(); ++j) {
      if (mat[i][j] < min) {
        tempRowIndexs[i] = std::stack<int>();
        min = mat[i][j];
        tempRowIndexs[i].push(j);
        continue;
      }
      if (mat[i][j] == min) {
        tempRowIndexs[i].push(j);
        continue;
      }
    }
  }

  // for each col storing the max value
  std::vector<std::set<int>> tempColIndexs(mat.front().size());
  for (int i = 0; i < mat.front().size(); ++i) {
    int max = INT_MIN;
    for (int j = 0; j < mat.size(); ++j) {
      if (mat[j][i] > max) {
        tempColIndexs[i].clear();
        max = mat[j][i];
        tempColIndexs[i].insert(j);
        continue;
      }
      if (mat[j][i] == max) {
        tempColIndexs[i].insert(j);
        continue;
      }
    }
  }

  dest.clear();
  for (int i = 0; i < tempRowIndexs.size(); ++i) {
    while (!tempRowIndexs[i].empty()) {
      const int j = tempRowIndexs[i].top();
      tempRowIndexs[i].pop();
      if (tempColIndexs[j].find(i) != tempColIndexs[j].end()) {
        dest.push_back({i, j});
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  std::vector<std::vector<int>> mat{
      {1, 2, 3, 1, 2, 3, 4},
      {9, 7, 6, 7, 7, 7, 10},
      {7, 8, 4, 8, 7, 7, 10},
      {6, 6, 4, 8, 6, 5, 8},
  };

  std::vector<std::pair<int, int>> result;
  saddlePoints(result, mat);
  for (const auto &pair : result) {
    cout << mat[pair.first][pair.second] << " @(" << pair.first << ", "
         << pair.second << ')' << std::endl;
  }

  return 0;
}