#include <cctype>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;

template <typename T> struct CSNode {
  using NodePtr = CSNode<T> *;

  T data;
  NodePtr firstChild, nextSibling;

  CSNode<T>(T data = T(), NodePtr firstChild = nullptr,
            NodePtr nextSibling = nullptr)
      : data(data), firstChild(firstChild), nextSibling(nextSibling) {}
};

CSNode<char> *CreateTree(std::string src) {
  if (src.empty()) {
    return nullptr;
  }
  const char headData = src.front();
  CSNode<char> *result = new CSNode<char>(headData);

  // const size_t leftBrIndex = src.find("(");
  // if (leftBrIndex == std::string::npos) {
  //   return result;
  // }
  if (src.size() < 3) {
    return result;
  }

  src.erase(src.begin(), src.begin() + 2);
  src.erase(src.end() - 1, src.end());
  std::stringstream ss(src);
  std::vector<std::string> childDatas;
  while (ss.good()) {
    std::string temp;

    char nextCh;
    ss >> nextCh;
    if (!isalpha(nextCh)) {
      continue;
    }
    temp.push_back(nextCh);

    ss >> nextCh;
    if (nextCh == '(') {
      while (nextCh != ')') {
        temp.push_back(nextCh);
        ss >> nextCh;
      }
      temp.push_back(')');
    }
    childDatas.push_back(temp);
  }
  for (const auto &str : childDatas) {
    cout << str << std::endl;
  }
  cout << std::endl;
  // "A(B(E,F),C(G),D(H,I,J))"
  result->firstChild = CreateTree(childDatas.front());
  CSNode<char> *layerTempPtr = result->firstChild;
  for (auto it = childDatas.begin() + 1; it < childDatas.end(); ++it) {
    layerTempPtr->nextSibling = CreateTree(*it);
    layerTempPtr = layerTempPtr->nextSibling;
  }
  return result;
}

template <typename T> void preOrderTraversal(CSNode<T> *const node) {
  cout << node->data << ' ';
  if (node->firstChild) {
    // cout << "go left" << std::endl;
    preOrderTraversal(node->firstChild);
  }
  if (node->nextSibling) {
    // cout << "go right" << std::endl;
    preOrderTraversal(node->nextSibling);
  }
};

template <typename T> void inOrderTraversal(CSNode<T> *const node) {
  if (node->firstChild) {
    // cout << "go left" << std::endl;
    inOrderTraversal(node->firstChild);
  }
  cout << node->data << ' ';
  if (node->nextSibling) {
    // cout << "go right" << std::endl;
    inOrderTraversal(node->nextSibling);
  }
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  const auto root = CreateTree("A(B(E,F),C(G),D(H,I,J))");
  preOrderTraversal(root);
  cout << std::endl;
  inOrderTraversal(root);
  cout << std::endl;
  return 0;
}