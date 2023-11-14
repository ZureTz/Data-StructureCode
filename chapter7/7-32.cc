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