#include <cstddef>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using std::cin;
using std::cout;

struct Node {
  int x, y, cost;

  Node(int x = 0, int y = 0, int cost = 0) : x(x), y(y), cost(cost) {}
  inline bool isLegal(int xSize, int ySize) const {
    return (0 <= x && x < xSize) && (0 <= y && y < ySize);
  }

  // struct cmp {
  //   inline bool operator()(const Node &n1, const Node &n2) const {
  //     return std::tie(n1.cost, n1.x, n1.y) > std::tie(n2.cost, n2.x, n2.y);
  //   }
  // };
};

struct pairHash {
  std::size_t operator()(const std::pair<int, int> &tag) const {
    return std::hash<int>()(tag.first) ^ (std::hash<int>()(tag.second) << 1);
  }
};

namespace {
const std::vector<std::pair<int, int>> directions = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};
} // namespace

long long minimumCost(
    // const arguments
    const std::unordered_map<std::pair<int, int>, long long, pairHash> &customers,
    const std::unordered_set<std::pair<int, int>, pairHash> &blockedPoints,
    const int mapSize,
    // non-const arguments
    std::unordered_set<std::pair<int, int>, pairHash> &visitedPos,
    std::queue<Node> &Queue) {

  long long result = 0ll;
  while (!Queue.empty()) {
    Node currentNode = Queue.front();
    Queue.pop();
    auto found = customers.find({currentNode.x, currentNode.y});
    if (found != customers.end()) {
      result += currentNode.cost * found->second;
    }
    for (int i = 0; i < directions.size(); ++i) {
      const int newX = currentNode.x + directions[i].first;
      const int newY = currentNode.y + directions[i].second;
      const int newCost = currentNode.cost + 1;
      Node newNode(newX, newY, newCost);
      if (!newNode.isLegal(mapSize, mapSize) ||
          blockedPoints.find({newX, newY}) != blockedPoints.end()) {
        continue;
      }
      if (visitedPos.find({newNode.x, newNode.y}) == visitedPos.end()) {
        visitedPos.insert({newNode.x, newNode.y});
        Queue.push(newNode);
      }
    }
  }
  return result;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nMapSize, mShopsCount, kCustomers, dBlockedPoints;
  cin >> nMapSize >> mShopsCount >> kCustomers >> dBlockedPoints;

  std::unordered_set<std::pair<int, int>, pairHash> visitedPos;
  std::queue<Node> Queue;
  for (int i = 0; i < mShopsCount; ++i) {
    int x, y;
    cin >> x >> y;
    Queue.emplace(x - 1, y - 1, 0);
    visitedPos.insert({x - 1, y - 1});
  }

  std::unordered_map<std::pair<int, int>, long long, pairHash> customers;
  for (int i = 0; i < kCustomers; ++i) {
    int x, y;
    long long serves;
    cin >> x >> y >> serves;
    customers[{x - 1, y - 1}] += serves;
  }

  std::unordered_set<std::pair<int, int>, pairHash> blockedPoints;
  for (int i = 0; i < dBlockedPoints; ++i) {
    int blockedX, blockedY;
    cin >> blockedX >> blockedY;
    blockedPoints.insert({blockedX - 1, blockedY - 1});
  }

  const long long cost =
      minimumCost(customers, blockedPoints, nMapSize, visitedPos, Queue);
  cout << cost << std::endl;

  return 0;
}