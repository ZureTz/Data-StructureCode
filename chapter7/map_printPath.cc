#include "graph.h"
#include <iostream>

void FindPath(book::ALGraph *G, int stack[], int &stackSize, int dest,
              int &isexist) {
  if (stack[stackSize - 1] == dest) { // full path to dest found, put result
    for (int i = 0; i < stackSize; ++i) {
      std::cout << stack[i] << ' ';
    }
    std::cout.put('\n');
    isexist = true;
    return;
  }

  for (int i = 0; i < stackSize - 1; ++i) {
    if (stack[i] == stack[stackSize - 1]) { // cycle found, terminiate
      return;
    }
  }

  // performing next level DFS
  const int currentVertex = stack[stackSize - 1];
  book::ArcNode *node = G->vertices[currentVertex].first;
  while (node) {
    stack[stackSize++] = node->adjvex;
    FindPath(G, stack, stackSize, dest, isexist);
    stackSize--;

    node = node->next;
  }
}

inline void ExistPath(book::ALGraph *G, int u, int v, int &exist) {
  int *stack = new int[G->vexnum]();
  int stackSize = 1;
  stack[stackSize - 1] = u;
  FindPath(G, stack, stackSize, v, exist);
  delete [] stack;
}

int main(int argc, char const *argv[]) {

  book::ALGraph G;
  G.vexnum = 5;
  G.arcnum = 8;
  auto p = G.vertices[0].first = new book::ArcNode(4);
  p->next = new book::ArcNode(3), p = p->next;
  p->next = new book::ArcNode(1), p = p->next;

  p = G.vertices[1].first = new book::ArcNode(3);
  p->next = new book::ArcNode(2), p = p->next;
  p->next = new book::ArcNode(4), p = p->next;

  p = G.vertices[2].first = new book::ArcNode(3);

  p = G.vertices[3].first = new book::ArcNode(4);

  int exist = 0;
  ExistPath(&G, 0, 4, exist);
  std::cout << (exist ? "Exist" : "Not Exist") << '\n';

  return 0;
}