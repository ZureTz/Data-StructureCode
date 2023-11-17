#include "../graph.h"
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using std::cin;
using std::cout;

struct pairComp {
  using Pair = std::pair<int, int>;
  inline bool operator()(const Pair &p1, const Pair &p2) const {
    return std::tie(p1.first, p1.second) > std::tie(p2.first, p2.second);
  }
};

int minimumLength(const AdjacentList::Graph &graph, int src, int dest) {
  using Pair = std::pair<int, int>;

  std::vector<int> distance(graph.list.size(), std::numeric_limits<int>::max());
  distance[src] = 0;

  std::priority_queue<Pair, std::vector<Pair>, pairComp> pq;
  pq.push({0, src});

  while (!pq.empty()) {
    Pair vertex = pq.top();
    // cout << vertex.first << ' ' << vertex.second << '\n';
    pq.pop();
    auto edge = graph.list[vertex.second]->firstEdge;
    while (edge) {
      if (distance[edge->pointTo] > edge->edgeLength) {
        distance[edge->pointTo] = edge->edgeLength;
        pq.push({distance[edge->pointTo], edge->pointTo});
      }
      edge = edge->nextEdge;
    }
  }

  return distance[dest];
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int nVerticies, mEdges;
  cin >> nVerticies >> mEdges;

  AdjacentList::Graph graph;
  for (int i = 0; i < nVerticies; ++i) {
    graph.vertexPush(i);
  }
  for (int i = 0; i < mEdges; ++i) {
    int src, dest, length;
    cin >> src >> dest >> length;
    graph.edgeConnect(src - 1, dest - 1, length);
  }

  cout << minimumLength(graph, 0, nVerticies - 1);

  return 0;
}