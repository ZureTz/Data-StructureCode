# 算法题

## 前提：图的结构体定义

```c++
#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <functional>
#include <ostream>
#include <queue>
#include <unordered_set>
#include <vector>

namespace AdjacentMatrix {
struct Graph {
  std::vector<std::vector<int>> matrix;
  Graph(const int n) {
    matrix.resize(n);
    std::fill(matrix.begin(), matrix.end(), std::vector<int>(n, 0));
  }
  void edgeConnect(const int begin, const int end, const int length= 1) {
    matrix[begin][end] = length;
  }
};
} // namespace AdjacentMatrix

namespace AdjacentList {

struct EdgeNode {
  int pointTo;
  int edgeLength;
  EdgeNode *nextEdge;
  EdgeNode(int pointTo, int edgeLength = 1, EdgeNode *nextEdge = nullptr)
      : pointTo(pointTo), edgeLength(edgeLength), nextEdge(nextEdge) {}

  ~EdgeNode() { delete nextEdge; }
};

struct VertexNode {
  int data;
  EdgeNode *firstEdge;
  VertexNode(int data, EdgeNode *firstEdge = nullptr)
      : data(data), firstEdge(firstEdge) {}
  ~VertexNode() { delete firstEdge; }
};

struct Graph {
  std::vector<VertexNode *> list;

  Graph() {}

  void vertexPush(const int data) { list.push_back(new VertexNode(data)); }
  void edgeConnect(const int begin, const int end, const int edgeLength = 1) {
    if (begin >= list.size() || end >= list.size()) {
      return;
    }

    EdgeNode *beginPtr = list[begin]->firstEdge;
    if (beginPtr == nullptr) {
      list[begin]->firstEdge = new EdgeNode(end, edgeLength);
      return;
    }
    while (beginPtr->nextEdge) {
      if (beginPtr->pointTo == end) {
        return;
      }
      beginPtr = beginPtr->nextEdge;
    }
    beginPtr->nextEdge = new EdgeNode(end, edgeLength);
  }

  void DFS(std::ostream &os, int beginNode) {
    if (beginNode >= list.size()) {
      return;
    }
    std::unordered_set<VertexNode *> isVisited;
    std::function<void(VertexNode *)> dfs = [&os, &isVisited, &dfs,
                                             this](VertexNode *vertex) -> void {
      if (vertex == nullptr) {
        return;
      }
      if (isVisited.find(vertex) != isVisited.end()) {
        return;
      }
      os << vertex->data << ' ';
      isVisited.insert(vertex);
      EdgeNode *node = vertex->firstEdge;
      while (node) {
        dfs(list[node->pointTo]);
        node = node->nextEdge;
      }
    };
    dfs(list[beginNode]);
  }

  void BFS(std::ostream &os, int beginNode) {
    if (beginNode >= list.size()) {
      return;
    }
    std::unordered_set<VertexNode *> isVisited;
    std::queue<VertexNode *> traverseQueue;
    traverseQueue.push(list[beginNode]);

    while (!traverseQueue.empty()) {
      VertexNode *node = traverseQueue.front();
      traverseQueue.pop();
      if (isVisited.find(node) != isVisited.end()) {
        continue;
      }
      os << node->data << ' ';
      isVisited.insert(node);
      EdgeNode *edge = node->firstEdge;
      while (edge) {
        traverseQueue.push(list[edge->pointTo]);
        edge = edge->nextEdge;
      }
    }
  }

  ~Graph() {
    for (auto ptr : list) {
      delete ptr;
    }
  }
};

} // namespace AdjacentList

#endif
```

## 7-19

```c++
namespace AdjacentMultiList {
struct EdgeNode {
  int leftVertex, rightVertex;
  int edgeLength;
  EdgeNode *leftNextEdge, *rightNextEdge;
  EdgeNode(int leftVertex, int rightVertex, int edgeLength = 1,
           EdgeNode *leftNextEdge = nullptr, EdgeNode *rightNextEdge = nullptr)
      : leftVertex(leftVertex), rightVertex(rightVertex),
        edgeLength(edgeLength), leftNextEdge(leftNextEdge),
        rightNextEdge(rightNextEdge) {}
  ~EdgeNode() { delete leftNextEdge; }
};

struct VertexNode {
  int data;
  EdgeNode *firstEdge;
  VertexNode(int data, EdgeNode *firstEdge = nullptr)
      : data(data), firstEdge(firstEdge) {}
  ~VertexNode() { delete firstEdge; }
};

struct Graph {
  std::vector<VertexNode *> list;

  Graph(std::istream &is) {
    int nVertexes = 0, nEdges = 0;
    is >> nVertexes >> nEdges;
    list.reserve(nVertexes);
    for (int i = 0; i < nVertexes; ++i) {
      int data;
      is >> data;
      vertexPush(data);
    }

    for (int i = 0; i < nEdges; ++i) {
      int begin, end;
      is >> begin >> end;
      edgeConnect(begin, end);
    }

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  void vertexPush(const int data) { list.push_back(new VertexNode(data)); }
  void edgeConnect(const int begin, const int end, const int edgeLength = 1) {
    if (begin >= list.size() || end >= list.size()) {
      return;
    }
    if (isEdgeDuplicate(begin, end)) {
      return;
    }

    EdgeNode *beginPtr = list[begin]->firstEdge;
    if (beginPtr == nullptr) {
      list[begin]->firstEdge = beginPtr = new EdgeNode(begin, end);
    } else {
      while (beginPtr->leftNextEdge) {
        beginPtr = beginPtr->leftNextEdge;
      }
      beginPtr->leftNextEdge = new EdgeNode(begin, end);
      beginPtr = beginPtr->leftNextEdge;
    }

    EdgeNode *endPtr = list[end]->firstEdge;
    if (endPtr == nullptr) {
      list[end]->firstEdge = endPtr = beginPtr;
    } else {
      while (endPtr->rightNextEdge) {
        endPtr = endPtr->rightNextEdge;
      }
      endPtr->rightNextEdge = beginPtr;
    }
  }

  bool isEdgeDuplicate(int beginVertex, int endVertex) {
    // first check
    EdgeNode *beginPtr = list[beginVertex]->firstEdge;
    while (beginPtr) {
      if (beginPtr->leftVertex == beginVertex &&
          beginPtr->rightVertex == endVertex) {
        return false;
      }
      beginPtr = beginPtr->leftNextEdge;
    }

    // second check
    EdgeNode *endPtr = list[endVertex]->firstEdge;
    while (endPtr) {
      if (endPtr->leftVertex == endVertex &&
          endPtr->rightVertex == beginVertex) {
        return false;
      }
      endPtr = endPtr->leftNextEdge;
    }

    return true;
  }

  ~Graph() {
    for (auto ptr : list) {
      delete ptr;
    }
  }
};

}; // namespace AdjacentMultiList
```

## 7-25

```c++
constexpr int MAX = 1001, n = 100;
static int s[MAX] = {0}, fst[n + 5] = {0}, lst[n + 5] = {0};
static bool isVisited[n + 5] = {false};

bool isCycle() {
  std::function<bool(int)> dfs = [&dfs](int index) -> bool {
    if (isVisited[index]) {
      return true;
    }

    int beginNode = fst[index], endNode = lst[index];
    if (beginNode > endNode) {
      return false;
    }

    isVisited[index] = true;
    bool flag = false;
    for (int i = beginNode; i <= endNode; ++i) {
      flag |= dfs(s[i]);
    }
    return flag;
  };

  bool flag = false;
  for (int i = 1; i <= n; ++i) {
    flag |= dfs(s[i]);
  }
  return flag;
}
```

## 7-26

```c++
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
```

## 7-32

```c++
#include "graph.h"
#include <functional>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace AdjacentList;

struct Tree {
  int data;
  Tree *child;
  Tree *nextSibling;
  Tree(int data = 0, Tree *child = nullptr, Tree *nextSibling = nullptr)
      : data(data), child(child), nextSibling(nextSibling) {}
  ~Tree() {
    delete child;
    delete nextSibling;
  }
};

struct Forest {
  std::vector<Tree *> trees;
  Forest() {}
  Forest(const Forest &forest) : trees(forest.trees) {}
  Forest(Forest &&forest) : trees(std::move(forest.trees)) {}
  void addTree(Tree *const tree) { trees.push_back(tree); }
  ~Forest() {
    for (Tree *tree : trees) {
      delete tree;
    }
  }
};

struct EdgeCompare {
  using pair = std::pair<int, EdgeNode *>;
  inline bool operator()(const pair &p1, const pair &p2) const {
    return p1.second->edgeLength > p2.second->edgeLength;
  }
};

Forest minimumSpanningForest(const Graph &graph) {
  std::unordered_set<VertexNode *> visitedNodes;
  auto minimumSpanningTree = [&](int index) -> Tree * {
    using pair = std::pair<int, EdgeNode *>;
    VertexNode *const node = graph.list[index];
    if (visitedNodes.find(node) != visitedNodes.end()) {
      return nullptr;
    }
    visitedNodes.insert(node);

    std::priority_queue<pair, std::vector<pair>, EdgeCompare> edgesQueue;
    EdgeNode *edge = node->firstEdge;
    while (edge) {
      edgesQueue.push({index, edge});
      edge = edge->nextEdge;
    }

    // initialize a graph
    Graph resultGraph;
    resultGraph.list.resize(graph.list.size(), nullptr);
    resultGraph.list[index] = graph.list[index];

    while (!edgesQueue.empty()) {
      pair currentEdge = edgesQueue.top();
      edgesQueue.pop();
      VertexNode *connectedVertex = graph.list[currentEdge.second->pointTo];
      if (visitedNodes.find(connectedVertex) != visitedNodes.end()) {
        continue;
      }

      visitedNodes.insert(connectedVertex);
      resultGraph.list[currentEdge.second->pointTo] = connectedVertex;
      resultGraph.edgeConnect(currentEdge.first, currentEdge.second->pointTo,
                              currentEdge.second->edgeLength);

      EdgeNode *connectedVertexEdge = connectedVertex->firstEdge;
      while (connectedVertexEdge) {
        edgesQueue.push({currentEdge.second->pointTo, connectedVertexEdge});
        connectedVertexEdge = connectedVertexEdge->nextEdge;
      }
    }

    // graph completed, build tree
    Tree *dummyHead = new Tree();

    std::queue<VertexNode *> traverseQueue;
    traverseQueue.push(graph.list[index]);
    int layerCount = 1;
    Tree *layerPtr = dummyHead;

    while (!traverseQueue.empty()) {
      VertexNode *firstNode = traverseQueue.front();
      traverseQueue.pop();

      layerPtr->child = new Tree(firstNode->data);
      layerPtr = layerPtr->child;
      layerCount--;

      EdgeNode *parentEdge = firstNode->firstEdge;
      while (parentEdge) {
        traverseQueue.push(graph.list[parentEdge->pointTo]);
        parentEdge = edge->nextEdge;
      }

      Tree *childPtr = layerPtr;
      while (layerCount-- > 0) {
        VertexNode *siblingNode = traverseQueue.front();
        traverseQueue.pop();

        childPtr->nextSibling = new Tree(siblingNode->data);
        childPtr = childPtr->nextSibling;

        EdgeNode *childEdge = siblingNode->firstEdge;
        while (childEdge) {
          traverseQueue.push(graph.list[childEdge->pointTo]);
          childEdge = childEdge->nextEdge;
        }
      }
      layerCount = traverseQueue.size();
    }
    return dummyHead->child;
  };

  Forest result;
  for (int i = 0; i < graph.list.size(); ++i) {
    Tree *treeNode = minimumSpanningTree(i);
    if (treeNode == nullptr) {
      continue;
    }
    result.addTree(treeNode);
  }
  return result;
}
```

## 7-41

```c++
#include "graph.h"
#include <algorithm>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace AdjacentList;

void printCriticalPath(const Graph &graph) {
  // step 1: compute the indegree foreach vertex
  std::vector<int> inDegree(graph.list.size(), 0);
  for (int i = 0; i < graph.list.size(); ++i) {
    EdgeNode *edge = graph.list[i]->firstEdge;
    while (edge) {
      inDegree[edge->pointTo]++;
      edge = edge->nextEdge;
    }
  }

  // step 2: topological sort
  std::queue<int> sortQueue;
  std::deque<int> topologicalOrder;
  for (int i = 0; i < graph.list.size(); ++i) {
    if (inDegree[i] == 0) {
      sortQueue.push(i);
    }
  }
  while (!sortQueue.empty()) {
    int index = sortQueue.front();
    sortQueue.pop();
    topologicalOrder.push_back(index);

    EdgeNode *edge = graph.list[index]->firstEdge;
    while (edge) {
      inDegree[edge->pointTo]--;
      if (inDegree[edge->pointTo] == 0) {
        sortQueue.push(edge->pointTo);
      }
      edge = edge->nextEdge;
    }
  }

  // step 3: compute the earliest start time for each vertex
  std::vector<int> earliestStartTime(graph.list.size(), 0);
  for (const int vertexIndex : topologicalOrder) {
    EdgeNode *edge = graph.list[vertexIndex]->firstEdge;
    while (edge) {
      int dest = edge->pointTo;
      int weight = edge->edgeLength;
      earliestStartTime[dest] = std::max(
          earliestStartTime[dest], earliestStartTime[vertexIndex] + weight);

      edge = edge->nextEdge;
    }
  }
  for (int i = 0; i < graph.list.size(); ++i) {
    std::cout << earliestStartTime[i] << ' ';
  }
  std::cout << std::endl;

  // step 4: compute the latest start time for each vertex
  std::vector<int> latestStartTime(graph.list.size(),
                                   std::numeric_limits<int>::max());
  latestStartTime[topologicalOrder[graph.list.size() - 1]] =
      earliestStartTime[topologicalOrder[graph.list.size() - 1]];
  for (int i = graph.list.size() - 2; i >= 0; --i) {
    int vertex = topologicalOrder[i];
    EdgeNode *edge = graph.list[vertex]->firstEdge;
    while (edge) {
      int dest = edge->pointTo;
      int weight = edge->edgeLength;
      latestStartTime[vertex] =
          std::min(latestStartTime[vertex], latestStartTime[dest] - weight);
          
      edge = edge->nextEdge;
    }
  }
  for (int i = 0; i < graph.list.size(); ++i) {
    std::cout << latestStartTime[i] << ' ';
  }
  std::cout << std::endl;

  // step 5: compute slack
  std::vector<int> slack(graph.list.size());
  for (int i = 0; i < graph.list.size(); ++i) {
    slack[i] = latestStartTime[i] - earliestStartTime[i];
    std::cout << slack[i] << ' ';
  }
  std::cout << std::endl;

  // step 6: print critical path
  std::cout << "Critical Path: ";
  EdgeNode *edge = graph.list[topologicalOrder[0]]->firstEdge;
  std::cout << graph.list[topologicalOrder[0]]->data << ' ';
  while (edge) {
    if (slack[edge->pointTo] == 0) {
      std::cout << graph.list[edge->pointTo]->data << ' ';
      edge = graph.list[edge->pointTo]->firstEdge;
      continue;
    }
    edge = edge->nextEdge;
  }
  std::cout << std::endl;
}

```

## 7-42

```c++
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
```