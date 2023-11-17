#include "../graph.h"
#include <iostream>
#include <queue>
#include <vector>
using std::cout;

bool DFSFindPath(const AdjacentList::Graph &graph, std::vector<bool> &isVisited,
                 int source, int destination) {
  if (source == destination) {
    return true;
  }
  isVisited[source] = true;
  for (auto edge = graph.list[source]->firstEdge; edge; edge = edge->nextEdge) {
    if (isVisited[edge->pointTo]) {
      continue;
    }
    if (DFSFindPath(graph, isVisited, edge->pointTo, destination)) {
      return true;
    }
  }
  return false;
}

bool BFSFindPath(const AdjacentList::Graph &graph, std::vector<bool> &isVisited,
                 int source, int destination) {
  std::queue<int> visitQueue;
  visitQueue.emplace(source);
  isVisited[source] = true;
  while (!visitQueue.empty()) {
    const int curr = visitQueue.front();
    visitQueue.pop();
    if (curr == destination) {
      break;
    }
    for (auto edge = graph.list[curr]->firstEdge; edge; edge = edge->nextEdge) {
      if (!isVisited[edge->pointTo]) {
        visitQueue.emplace(edge->pointTo);
        isVisited[edge->pointTo] = true;
      }
    }
  }
  return isVisited[destination];
}

bool ifPathExist(const AdjacentList::Graph &graph, int source,
                 int destination) {
  std::vector<bool> DFSisVisited(graph.list.size(), false);
  std::vector<bool> BFSisVisited(graph.list.size(), false);

  return DFSFindPath(graph, DFSisVisited, source, destination) &&
         BFSFindPath(graph, BFSisVisited, source, destination);
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  AdjacentList::Graph graph;

  for (int i = 0; i < 9; ++i) {
    graph.vertexPush(i);
  }
  graph.edgeConnect(0, 1, 2);
  graph.edgeConnect(0, 2, 5);
  graph.edgeConnect(0, 4, 5);
  graph.edgeConnect(1, 2, 2);
  graph.edgeConnect(1, 3, 3);
  graph.edgeConnect(2, 4, 1);
  graph.edgeConnect(2, 5, 3);
  graph.edgeConnect(3, 5, 2);
  graph.edgeConnect(4, 6, 6);
  graph.edgeConnect(5, 6, 3);
  graph.edgeConnect(5, 7, 4);
  graph.edgeConnect(6, 8, 4);
  graph.edgeConnect(7, 8, 2);

  cout << (ifPathExist(graph, 0, 4) ? 'T' : 'F') << '\n';
  cout << (ifPathExist(graph, 1, 7) ? 'T' : 'F') << '\n';
  cout << (ifPathExist(graph, 3, 2) ? 'T' : 'F') << '\n';

  return 0;
}