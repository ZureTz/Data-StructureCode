#include "binary_tree.h"
#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
using std::cout;

template <typename T> size_t getHeight(TreeNode<T> *root) {
  if (root == nullptr) {
    return 0;
  }
  return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

template <typename T>
std::deque<std::deque<T>> treeTable(TreeNode<T> *root, const size_t height,
                                    const size_t currentIndex = 0) {
  if (root == nullptr) {
    return std::deque<std::deque<T>>();
  }

  std::deque<std::deque<T>> leftResult =
      treeTable(root->left, height, currentIndex + 1);

  std::deque<std::deque<T>> result(1, std::deque<T>(height, T()));
  result[0][currentIndex] = root->data;

  std::deque<std::deque<T>> rightResult =
      treeTable(root->right, height, currentIndex + 1);

  result.insert(result.begin(), rightResult.begin(), rightResult.end());
  result.insert(result.end(), leftResult.begin(), leftResult.end());

  return result;
}

template <typename T> void printTreeAsTable(TreeNode<T> *root) {
  if (root == nullptr) {
    return;
  }
  const size_t height = getHeight(root);
  const auto result = treeTable(root, height);
  for (const auto row : result) {
    for (const T data : row) {
      if (data == T()) {
        cout << std::setw(5) << std::setfill(' ') << ' ' << " ";
        continue;
      }
      cout << std::setw(5) << std::setfill(' ') << data << " ";
    }
    cout << '\n';
  }
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
  BinaryTree<int> tree{2, 3, 5, 7, 11, 13, 15, 24, 4,
                       5, 6, 7, 8, 9,  24, -5, -77};
  printTreeAsTable(tree.root);
  cout << std::endl;

  recursive::reverseTree(tree.root);
  printTreeAsTable(tree.root);

  cout << std::endl;

  return 0;
}