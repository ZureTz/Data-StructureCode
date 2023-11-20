#include "../graph.h"
#include <deque>
#include <iostream>
#include <vector>
using std::cout;

void dfs(const AdjacentList::Graph &graph, std::vector<bool> &isVisited,
         std::deque<int> &dest, int node) {
  if (isVisited[node]) {
    return;
  } 
  isVisited[node] = true;
  AdjacentList::EdgeNode *edge = graph.list[node]->firstEdge;
  while (edge) {
    dfs(graph, isVisited, dest, edge->pointTo);
    edge = edge->nextEdge;
  }
  dest.push_front(node);
}

std::deque<int> topologicalsort(const AdjacentList::Graph &graph) {
  std::vector<bool> isVisited(graph.list.size(), false);
  std::deque<int> result;
  for (int i = graph.list.size() - 1; i >= 0; --i) {
    dfs(graph, isVisited, result, i);
  }
  return result;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  AdjacentList::Graph graph;
  for (int i = 0; i < 6; ++i) {
    graph.vertexPush(i);
  }
  std::vector<std::vector<int>> mat{
      {0, 1, 1, 1, 0, 0},
      {0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 0},
      {0, 0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 0},
  };

  for (int i = 0; i < mat.size(); ++i) {
    for (int j = mat[i].size() - 1; j >= 0; --j) {
      if (mat[i][j]) {
        graph.edgeConnect(i, j);
      }
    }
  }

  auto res = topologicalsort(graph);
  for (const int node : res) {
    cout << node << ' ';
  }

  return 0;
}