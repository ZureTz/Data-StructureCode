#include <iostream>
#include <set>
#include <tuple>
#include <utility>
using std::cin;
using std::cout;

struct timeComp {
  bool operator()(const std::pair<int, int> &p1,
                  const std::pair<int, int> &p2) const {
    return std::tie(p1.first, p1.second) < std::tie(p2.first, p2.second);
  }
};

inline int reSize(const int n) { return n < 0 ? 0 : n; }

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  size_t nTimeSeq;
  cin >> nTimeSeq;
  std::set<std::pair<int, int>, timeComp> timeSeqSet;
  for (size_t i = 0, iters(2 * nTimeSeq), tempBegin, tempEnd; i < iters; i++) {
    cin >> tempBegin >> tempEnd;
    timeSeqSet.insert({tempBegin, tempEnd});
  }

  int togetherTime(0);
  {
    auto itNow = timeSeqSet.begin();
    auto itPrev = itNow++;
    while (itNow != timeSeqSet.end()) {
      // cout << itPrev->first << ' ' << itPrev->second << ", " << itNow->first
      //      << ' ' << itNow->second << ", diff: "
      //      << reSize(itPrev->second - itNow->first -
      //                reSize(itPrev->second - itNow->second))
      //      << std::endl;
      togetherTime += reSize(itPrev->second - itNow->first -
                             reSize(itPrev->second - itNow->second));
      itPrev = itNow++;
    }
  }
  cout << togetherTime << std::endl;

  return 0;
}