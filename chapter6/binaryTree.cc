#include <functional>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <queue>
using std::cin;
using std::cout;

template <typename T> struct TreeNode {
  using NodePtr = TreeNode<T> *;

  T data;
  NodePtr left;
  NodePtr right;

  TreeNode<T>(T data = T(), NodePtr left = nullptr, NodePtr right = nullptr)
      : data(data), left(left), right(right) {}
};

template <typename T> struct BinaryTree {
  using NodePtr = TreeNode<T> *;

  NodePtr const root;

  BinaryTree<T>(const std::initializer_list<T> &list)
      : root(new TreeNode<T>(*list.begin())) {
    cout << "initialising..." << std::endl;

    std::queue<NodePtr> insertQueue;
    insertQueue.push(root);

    bool insertFlag = true;
    auto it = list.begin() + 1;
    while (it != list.end()) {
      NodePtr tempPtr = insertQueue.front();
      insertQueue.pop();

      tempPtr->left = new TreeNode<T>(*it++);
      insertQueue.push(tempPtr->left);
      if (it == list.end()) {
        break;
      }

      tempPtr->right = new TreeNode<T>(*it++);
      insertQueue.push(tempPtr->right);
    }
  }
};

template <typename T> void preOrderTraversal(TreeNode<T> *const node) {
  cout << node->data << ' ';
  if (node->left) {
    // cout << "go left" << std::endl;
    preOrderTraversal(node->left);
  }
  if (node->right) {
    // cout << "go right" << std::endl;
    preOrderTraversal(node->right);
  }
};

template <typename T> void inOrderTraversal(TreeNode<T> *const node) {
  if (node->left) {
    // cout << "go left" << std::endl;
    inOrderTraversal(node->left);
  }
  cout << node->data << ' ';
  if (node->right) {
    // cout << "go right" << std::endl;
    inOrderTraversal(node->right);
  }
};

template <typename T> void postOrderTraversal(TreeNode<T> *const node) {
  if (node->left) {
    // cout << "go left" << std::endl;
    postOrderTraversal(node->left);
  }
  if (node->right) {
    // cout << "go right" << std::endl;
    postOrderTraversal(node->right);
  }
  cout << node->data << ' ';
};

template <typename T> void layerOrderTraversal(TreeNode<T> *const node) {
  std::queue<TreeNode<T> *> traverseQueue;
  traverseQueue.push(node);
  while (!traverseQueue.empty()) {
    TreeNode<T> *const temp = traverseQueue.front();
    traverseQueue.pop();
    cout << temp->data << ' ';
    if (temp->left) {
      traverseQueue.push(temp->left);
    }
    if (temp->right) {
      traverseQueue.push(temp->right);
    }
  }
}

int main(int argc, char const *argv[]) {
  BinaryTree<int> tree{2, 3, 5, 7, 11, 13, 15, 24};
  preOrderTraversal(tree.root);
  cout.put('\n');
  inOrderTraversal(tree.root);
  cout.put('\n');
  postOrderTraversal(tree.root);
  cout.put('\n');
  layerOrderTraversal(tree.root);
  cout.put('\n');
  // TreeNode<int> *ptr = tree.root;
  // while (ptr) {
  //   cout << ptr->data << ' ';
  //   ptr = ptr->left;
  // }
  return 0;
}