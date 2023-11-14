#include <ios>
#include <iostream>
#include <istream>
#include <limits>
using std::cout;

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

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  AdjacentMultiList::Graph graph(std::cin);

  return 0;
}