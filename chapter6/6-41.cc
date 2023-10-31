#include "binary_tree.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
using std::cout;

template <typename T> T *recursiveAccess(TreeNode<T> *node, size_t &pos) {
  if (node == nullptr || pos == 0) {
    return nullptr;
  }

  --pos;
  if (pos == 0) {
    return &(node->data);
  }

  T *leftResult = recursiveAccess(node->left, pos);
  if (leftResult) {
    return leftResult;
  }
  T *rightResult = recursiveAccess(node->right, pos);
  if (rightResult) {
    return rightResult;
  }

  return nullptr;
}
template <typename T> inline T preOrderAccess(TreeNode<T> *root, size_t k) {
  T *resultPtr = recursiveAccess(root, k);
  if (resultPtr == nullptr) {
    std::cerr << "Out of bound" << std::endl;
    exit(EXIT_FAILURE);
  }
  return *resultPtr;
}

int main(int argc, char const *argv[]) {
  /*
              2
             / \
            /   \
           /     \
          /       \
         3         5
        / \       / \
       /   \     /   \
      7    11   13   15
     / \  / \
    24 4 5  6
  */
  BinaryTree<int> tree{
      2, 3, 5, 7, 11, 13, 15, 24, 4, 5, 6,
  };
  for (int i = 1; i <= 11; ++i) {
    cout << preOrderAccess(tree.root, i) << ' ';
  }
  cout << std::endl;

  iterative::preOrderTraversal(tree.root);

  return 0;
}