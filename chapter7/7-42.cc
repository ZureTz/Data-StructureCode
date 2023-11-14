#include "graph.h"
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
using std::cout;
using namespace AdjacentList;

struct pairCompare {
  using Pair = std::pair<int, int>;
  inline bool operator()(const Pair &p1, const Pair &p2) const {
    return p1.first > p2.first;
  }
};

// using Dijsktra Algorithm
void printShortestPath(const Graph &graph, int begin) {
  using Pair = std::pair<int, int>;

  std::vector<int> distance(graph.list.size(), std::numeric_limits<int>::max());
  // first: weight, second: vertexIndex
  std::priority_queue<Pair, std::vector<Pair>, pairCompare> pq;
  pq.push({0, begin});
  while (!pq.empty()) {
    Pair vertex = pq.top();
    pq.pop();
    EdgeNode *edge = graph.list[vertex.second]->firstEdge;
    while (edge) {
      if (distance[edge->pointTo] >
          distance[vertex.second] + edge->edgeLength) {
        distance[edge->pointTo] = distance[vertex.second] + edge->edgeLength;
        pq.push({distance[edge->pointTo], edge->pointTo});
      }
      edge = edge->nextEdge;
    }
  }

  for (const int dist : distance) {
    cout << dist << ' ';
  }
  cout << std::endl;
}