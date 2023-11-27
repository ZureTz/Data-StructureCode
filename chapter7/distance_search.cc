#include "graph.h"
#include <iostream>
#include <queue>
using std::cout;

// Given a graph(stored in book::AdjList), and a node n, return all nodes that
// is kth shortest distance from node

// The argument has problem: ver[]'s length is not defined, may cause outofbound
// errer.(using sizeof() does not make effect because the ver decays as a
// pointer)

// Also, ver[] cannot be reallocated since the caller of this function
// only knows the original address.
void BFS_k(book::ALGraph &G, int v, int k, int ver[], int &n) {
  std::queue<int> BFSQueue;
  BFSQueue.push(v);

  bool *isVisited = new bool[G.vexnum]();
  while (k-- > 0) {
    int currentSize = BFSQueue.size();
    while (currentSize-- > 0) {
      const int vertexIndex = BFSQueue.front();
      BFSQueue.pop();
      if (isVisited[vertexIndex]) {
        continue;
      }
      isVisited[vertexIndex] = true;

      book::ArcNode *ptr = G.vertices[vertexIndex].first;
      while (ptr) {
        BFSQueue.push(ptr->adjvex);
        ptr = ptr->next;
      }
    }
  }

  n = 0;
  while (!BFSQueue.empty()) {
    const int currentVertex = BFSQueue.front();
    BFSQueue.pop();
    if (isVisited[currentVertex]) {
      continue;
    }
    ver[n++] = currentVertex;
  }

  delete[] isVisited;
}

int main(int argc, char const *argv[]) {

  book::ALGraph G;
  G.arcnum = 9, G.vexnum = 8;
  auto p = G.vertices[0].first = new book::ArcNode(1);
  p = G.vertices[1].first = new book::ArcNode(3);
  p = G.vertices[2].first = new book::ArcNode(1);
  p = G.vertices[3].first = new book::ArcNode(2);
  p->next = new book::ArcNode(4);
  p = G.vertices[4].first = new book::ArcNode(5);
  p = G.vertices[5].first = new book::ArcNode(7);
  p = G.vertices[6].first = new book::ArcNode(4);
  p = G.vertices[7].first = new book::ArcNode(6);

  int *distVertecies = new int[G.vexnum]();
  int numOfVerticies = 0;

  BFS_k(G, 3, 0, distVertecies, numOfVerticies);

  for (int i = 0; i < numOfVerticies; ++i) {
    cout << distVertecies[i] << ' ';
  }

  delete[] distVertecies;

  return 0;
}