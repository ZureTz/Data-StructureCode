#include <cstddef>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using std::cout;

struct pairHash {
  std::size_t operator()(const std::pair<int, int> &pair) const {
    return std::hash<int>()(pair.first) ^ (std::hash<int>()(pair.second) << 1);
  }
};

std::unordered_map<std::pair<int, int>, unsigned long long, pairHash> DPMap;

unsigned long long getRoutes(
    const std::pair<int, int> &current, const std::pair<int, int> &dest,
    const std::unordered_set<std::pair<int, int>, pairHash> &blockcedPoints) {

  auto blockedFound = blockcedPoints.find(current);
  if (blockedFound != blockcedPoints.end()) {
    return 0ull;
  }

  if (current.first == dest.first || current.second == dest.second) {
    return 1ull;
  }

  auto prevFound = DPMap.find(current);
  if (prevFound != DPMap.end()) {
    return prevFound->second;
  }

  const unsigned long long res =
      getRoutes(std::make_pair(current.first + 1, current.second), dest,
                blockcedPoints) +
      getRoutes(std::make_pair(current.first, current.second + 1), dest,
                blockcedPoints);
  DPMap.insert({current, res});
  return res;
}

int main(int argc, char const *argv[]) {

  std::pair<int, int> destination;
  std::pair<int, int> horse;
  std::unordered_set<std::pair<int, int>, pairHash> blockcedPoints;

  std::cin >> destination.first >> destination.second;
  std::cin >> horse.first >> horse.second;

  const std::vector<std::pair<int, int>> horseMoveRange{
      {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2},
  };

  blockcedPoints.insert(horse);
  for (const auto &range : horseMoveRange) {
    blockcedPoints.insert(
        {horse.first + range.first, horse.second + range.second});
  }

  cout << getRoutes(std::make_pair(0, 0), destination, blockcedPoints)
       << std::endl;

  return 0;
}