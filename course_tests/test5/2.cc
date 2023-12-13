#include <algorithm>
#include <cstring>
#include <iostream>
using std::cin;
using std::cout;

constexpr int N = 3005;
constexpr int M = 15;

int main(int argc, char const *argv[]) {
  int n, m;
  int dp[N][M], sum[N], a[N];

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  std::sort(a + 1, a + n + 1);

  for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + a[i];
  }
  memset(dp, 63, sizeof dp);

  auto getColor = [&](int l, int r) {
    const int mid = (l + r) / 2;
    return a[mid] * (mid - l) - sum[mid - 1] + sum[l - 1] - a[mid] * (r - mid) +
           sum[r] - sum[mid];
  };

  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 0; k < i; k++) {
        dp[i][j] = std::min(dp[i][j], dp[k][j - 1] + getColor(k + 1, i));
      }
    }
  }
  (cout << dp[n][m]).put('\n');

  return 0;
}