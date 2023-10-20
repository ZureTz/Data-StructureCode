#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <vector>
using std::cin;
using std::cout;
using ll = long long;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  ll n, m;
  cin >> n >> m;

  std::deque<ll> waitTimes;
  for (ll i = 0; i < n; ++i) {
    ll time;
    cin >> time;
    waitTimes.push_back(time);
  }
  std::sort(waitTimes.begin(), waitTimes.end());

  std::vector<ll> sumTime(m);
  ll result = 0;
  ll iter = 0;
  while (!waitTimes.empty()) {
    result += sumTime[iter];
    sumTime[iter] += waitTimes.front();
    waitTimes.pop_front();
    ++iter;
    if (iter == m) {
      iter = 0;
    }
  }
  cout << result;

  return 0;
}