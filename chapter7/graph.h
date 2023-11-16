#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <initializer_list>
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
  Graph(const std::initializer_list<int> &source) {
    for (const int data : source) {
      vertexPush(data);
    }
  }

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