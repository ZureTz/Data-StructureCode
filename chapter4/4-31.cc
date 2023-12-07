#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
using std::vector;
using std::string;
using std::pair;

// // Return the length of LCS for X[0...m-1] and Y[0...n-1]
// int lcs(const string &X, const string &Y, int m, int n)
// {
// 	if (m == 0 || n == 0)
// 		return 0;
// 	if (X[m-1] == Y[n-1])
// 		return lcs(X, Y, m-1, n-1) + 1;
// 	else
// 		return 0;
// }

size_t LCSubStrSize(const string &x, const string &y, size_t m,
                    size_t n) {
  vector<vector<size_t>> dp(m + 1, vector<size_t>(n + 1, 0));
  size_t max = 0;
  for (int i = 1; i < m + 1; ++i) {
    for (int j = 1; j < n + 1; ++j) {
      if (x[i - 1] == y[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        max = std::max(max, dp[i][j]);
      }
    }
  }
  return max;
}

vector<string> LCSubStrs(const string &x, const string &y,
                                   size_t m, size_t n) {
  vector<vector<size_t>> dp(m + 1, vector<size_t>(n + 1, 0));
  size_t max = 0;
  for (size_t i = 1; i < m + 1; ++i) {
    for (size_t j = 1; j < n + 1; ++j) {
      if (x[i - 1] == y[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        max = std::max(max, dp[i][j]);
      }
    }
  }

  std::cout << max << std::endl;
  vector<string> result;
  pair<size_t, size_t> iMinPos = {std::numeric_limits<size_t>::max(), 0};
  for (size_t i = 1; i < m + 1; ++i) {
    for (size_t j = 1; j < n + 1; ++j) {
      if (dp[i][j] == max) {
        if (i < iMinPos.first) {
          iMinPos.first = i;
          iMinPos.second = j;
        }
        string temp;
        size_t iTemp(i), jTemp(j);
        while (dp[iTemp][jTemp] > 0) {
          temp.push_back(x[iTemp - 1]);
          iTemp--;
          jTemp--;
        }
        result.emplace_back(string(temp.rbegin(), temp.rend()));
      }
    }
  }

  string temp;
  size_t iTemp(iMinPos.first), jTemp(iMinPos.second);
  while (dp[iTemp][jTemp] > 0) {
    temp.push_back(x[iTemp - 1]);
    iTemp--;
    jTemp--;
  }
  result.emplace_back(string(temp.rbegin(), temp.rend()));

  return result;
}
int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  const string s1("ABCBDAB");
  const string s2("BDCABA");
  std::cout << LCSubStrSize(s1, s2, s1.length(), s2.length()) << std::endl;
  const auto LCSSubStrings = LCSubStrs(s1, s2, s1.length(), s2.length());
  for (const string &str : LCSSubStrings) {
    std::cout << str << std::endl;
  }
  return 0;
}