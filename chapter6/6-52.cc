#include "binary_tree.h"
#include <algorithm>
#include <cstddef>
#include <queue>

template <typename T> size_t height(TreeNode<T> *root) {
  if (root == nullptr) {
    return 0;
  }
  return 1 + std::max(height(root->left), height(root->right));
}

template <typename T> size_t maxWidth(TreeNode<T> *root) {
  if (root == nullptr) {
    return 0;
  }
  std::queue<TreeNode<T> *> queue;
  queue.push(root);
  size_t result = 0;
  while (!queue.empty()) {
    size_t layerWidth = queue.size();
    result = std::max(result, layerWidth);
    while (layerWidth-- > 0) {
      TreeNode<T> *const temp = queue.front();
      queue.pop();
      if (temp->left) {
        queue.push(temp->left);
      }
      if (temp->right) {
        queue.push(temp->right);
      }
    }
  }
  return result;
}

template <typename T> inline size_t growthDegree(TreeNode<T> *root) {
  return height(root) * maxWidth(root);
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
  cout << growthDegree(tree.root);
  return 0;
}