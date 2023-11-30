#include <vector>
#include <unordered_map>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>

using std::cout;
using ull = unsigned long long;
constexpr ull base = 173;
constexpr int MAXLENGTH = 2010;

ull jc[MAXLENGTH], hashList[11][MAXLENGTH];
int sum[11][MAXLENGTH];
char str[11][MAXLENGTH];
int maxLength(0), maxLenghIdx(0);
int numOfStrings;

inline ull getHash(int strIndex, int l, int r) {
  return hashList[strIndex][r] - hashList[strIndex][l - 1] * jc[r - l + 1];
}

bool checkDuplicate(size_t mid) {
  std::vector<std::unordered_map<int, ull>> maps(11);

  for (int i = 1; i < numOfStrings; ++i) {
    const int iLength = strlen(str[i] + 1);
    for (int j = 1; j + mid - 1 <= iLength; ++j) {
      ull tempHash = getHash(i, j, j + mid - 1);
      maps[i][tempHash] = 1;
    }
  }

  const int nLength = strlen(str[numOfStrings] + 1);
  for (int i = 1; i + mid - 1 <= nLength; i++) {
    ull tmpHash = getHash(numOfStrings, i, i + mid - 1);
    bool flag = false;
    for (int j = 1; j < numOfStrings; j++)
      if (!maps[j][tmpHash]) {
        flag = true;
      }
    if (flag == false) {
      return true;
    }
  }
  return false;
}

int main(int argc, char const *argv[]) {

  std::cin >> numOfStrings;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  for (int i = 1; i <= numOfStrings; ++i) {
    scanf("%s", str[i] + 1);
    for (int j = 1; j <= strlen(str[i] + 1); j++)
      sum[i][j] = str[i][j] - 'a' + 1;
    if (strlen(str[i] + 1) > maxLength) {
      maxLength = strlen(str[i] + 1);
      maxLenghIdx = i;
    }
  }

  [&]() {
    jc[0] = 1;
    for (int i = 1; i <= 2000; i++) {
      jc[i] = jc[i - 1] * base;
    }
    for (int i = 1; i <= numOfStrings; i++) {
      for (int j = 1; j <= strlen(str[i] + 1); j++) {
        hashList[i][j] = hashList[i][j - 1] * base + sum[i][j];
      }
    }
  }();

  size_t answer = 0;

  size_t left = 1, right = maxLength;
  while (left <= right) {
    const int mid = (left + right) / 2;
    if (checkDuplicate(mid)) {
      answer = mid;
      left = mid + 1;
      continue;
    }
    right = mid - 1;
  }

  cout << answer << std::endl;

  return 0;
}