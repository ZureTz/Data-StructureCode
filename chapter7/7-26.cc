#include "graph.h"
#include <deque>
#include <functional>
#include <iostream>
#include <unordered_set>
using std::cout;

void getTriangleMatrixIndex(const AdjacentList::Graph &graph) {
  using namespace AdjacentList;

  std::unordered_set<VertexNode *> isVisited;
  std::deque<VertexNode *> outputQueue;
  std::function<void(VertexNode *)> dfs = [&](VertexNode *node) -> void {
    if (node == nullptr) {
      return;
    }
    if (isVisited.find(node) != isVisited.end()) {
      return;
    }
    isVisited.insert(node);
    EdgeNode *edge = node->firstEdge;
    while (edge) {
      dfs(graph.list[edge->pointTo]);
      edge = edge->nextEdge;
    }
    outputQueue.push_front(node);
  };
  for (VertexNode *node : graph.list) {
    dfs(node);
  }

  auto it = outputQueue.end() - 1;
  int i = 0;
  while (it >= outputQueue.begin()) {
    cout << (*it)->data << ": " << i << std::endl;
    --it, ++i;
  }
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  AdjacentList::Graph graph;
  for (int i = 0; i < 5; ++i) {
    graph.vertexPush(i);
  }
  graph.edgeConnect(0, 1);
  graph.edgeConnect(0, 2);
  graph.edgeConnect(0, 3);
  graph.edgeConnect(1, 2);
  graph.edgeConnect(2, 3);
  graph.edgeConnect(3, 4);

  getTriangleMatrixIndex(graph);

  return 0;
}