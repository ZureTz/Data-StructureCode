#include "binary_tree.h"
#include <iostream>
#include <sys/_types/_size_t.h>
using std::cout;

template <typename T> size_t leafNodeCount(TreeNode<T> *root) {
  if (root->left == nullptr && root->right == nullptr) {
    return 1;
  }
  size_t result = 0;
  if (root->left) {
    result += leafNodeCount(root->left);
  }
  if (root->right) {
    result += leafNodeCount(root->right);
  }
  return result;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
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
  BinaryTree<int> tree{2, 3, 5, 7, 11, 13, 15, 24, 4, 5, 6, 8, 9};
  cout << leafNodeCount(tree.root);
  return 0;
}