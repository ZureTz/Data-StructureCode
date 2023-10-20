#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <tuple>
#include <unordered_set>
#include <vector>
using std::cin;
using std::cout;
using ll = long long;

struct Company {
  ll index;
  ll priority;
  Company(ll index = 0ll, ll priority = 0ll)
      : index(index), priority(priority) {}
};

struct Task {
  ll time;
  ll taskIndex;
  Task(ll time = 0, ll index = 0) : time(time), taskIndex(index) {}
  bool operator==(const Task &rhs) const {
    return time == rhs.time && taskIndex == rhs.taskIndex;
  }
};

struct companyCmp {
  bool operator()(const Company &c1, const Company &c2) const {
    return std::tie(c1.priority, c1.index) < std::tie(c2.priority, c2.index);
  }
};

struct keyHasher {
  std::size_t operator()(const Task &op) const {
    return std::hash<ll>()(op.time) ^ (std::hash<ll>()(op.taskIndex) << 1);
  }
};

// struct taskComp {
// bool operator()(const Task &t1, const Task &t2) {
//     return std::tie(t1.time, t1.taskIndex) < std::tie(t2.time, t2.taskIndex);
//   }
// };

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  ll mComps, n, times;
  cin >> mComps >> n >> times;

  std::vector<ll> companys(mComps);
  std::set<ll> companyPriorityList;

  std::unordered_multiset<Task, keyHasher> inputTasks;
  for (int i = 0; i < n; ++i) {
    ll time, index;
    cin >> time >> index;
    inputTasks.insert(Task(time, index));
  }

  for (int i = 1; i <= times; ++i) {
    for (ll j = 0; j < mComps; ++j) {
      const ll count = inputTasks.count(Task(i, j + 1));
      if (count) {
        companys[j] += (2 * count);
        if (companys[j] > 5) {
          companyPriorityList.insert(j);
        }
        continue;
      }
      // else not found.
      companys[j]--;
      if (companys[j] <= 0) {
        companys[j] = 0;
      }
      if (companys[j] <= 3) {
        const auto itthen = companyPriorityList.find(j);
        if (itthen != companyPriorityList.end()) {
          companyPriorityList.erase(itthen);
        }
      }
    }
  }
  cout << companyPriorityList.size();

  return 0;
}