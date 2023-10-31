#include <algorithm>
#include <cstddef>
#include <vector>
constexpr size_t MAX_TREE_SIZE = 10000;

template <typename T> struct PTNode {
  T data;
  int parent;
};

template <typename T> struct PTree {
  PTNode<T> nodes[MAX_TREE_SIZE];
  int n, r;
  // n: child count
  // r: root index
};

template <typename T> struct CSNode {
  using NodePtr = CSNode<T> *;

  T data;
  NodePtr firstChild, nextSibling;

  CSNode<T>(T data = T(), NodePtr firstChild = nullptr,
            NodePtr nextSibling = nullptr)
      : data(data), firstChild(firstChild), nextSibling(nextSibling) {}
};

template <typename T> CSNode<T> *CreateCSTree(const PTree<T> &src) {
  std::vector<CSNode<T> *> ptrMap(src.n, nullptr);

  CSNode<T> *result = new CSNode<T>(src.nodes[src.r].data);
  ptrMap[src.r] = result;

  CSNode<T> *layerTempPtr = result;
  int index = 1;
  while (index < src.n) {
    const int commonParentIndex = src.nodes[index].parent;

    layerTempPtr->firstChild = new CSNode<T>(src.nodes[index].data);
    layerTempPtr = layerTempPtr->firstChild;
    ptrMap[index] = layerTempPtr;
    index++;

    CSNode<T> *siblingTempPtr = layerTempPtr;
    while (index < src.n && src.nodes[index].parent == commonParentIndex) {
      siblingTempPtr->nextSibling = new CSNode<T>(src[index].data);
      siblingTempPtr = siblingTempPtr->nextSibling;
      ptrMap[index] = siblingTempPtr;
      index++;
    }
    if (index >= src.n) {
      break;
    }
    if (index == src.r) {
      index++;
    }
    layerTempPtr = ptrMap[src[index].parent];
  }
  return result;
}