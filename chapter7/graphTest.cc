#include "graph.h"
#include <iostream>
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  AdjacentList::Graph graph{0, 1, 2, 3, 4};

  graph.edgeConnect(0, 1);
  graph.edgeConnect(1, 2);
  graph.edgeConnect(2, 0);
  graph.edgeConnect(2, 4);
  graph.edgeConnect(4, 3);
  graph.edgeConnect(3, 1);

  // for (int i = 0; i < 6; ++i) {
  //   graph.vertexPush(i + 1);
  // }
  // graph.edgeConnect(0, 1);
  // graph.edgeConnect(1, 2);
  // graph.edgeConnect(1, 3);
  // graph.edgeConnect(3, 0);
  // graph.edgeConnect(2, 4);
  // graph.edgeConnect(4, 5);
  // graph.edgeConnect(5, 2);

  graph.DFS(cout, 0);
  cout.put('\n');
  graph.BFS(cout, 0);
  cout.put('\n');

  return 0;
}