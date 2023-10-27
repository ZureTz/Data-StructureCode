#include <functional>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <queue>
#include <stack>
#include <utility>
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

namespace recursive {

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

} // namespace recursive

namespace iterative {

template <typename T> void preOrderTraversal(TreeNode<T> *const root) {
  std::stack<TreeNode<T> *> traverseStack;
  TreeNode<T> *node = root;
  while (node || !traverseStack.empty()) {
    while (node) {
      cout << node->data << ' ';
      traverseStack.push(node);
      node = node->left;
    }
    node = traverseStack.top();
    traverseStack.pop();
    node = node->right;
  }
};

template <typename T> void inOrderTraversal(TreeNode<T> *const root) {
  std::stack<TreeNode<T> *> traverseStack;
  TreeNode<T> *node = root;
  while (node || !traverseStack.empty()) {
    while (node) {
      traverseStack.push(node);
      node = node->left;
    }
    node = traverseStack.top();
    traverseStack.pop();
    cout << node->data << ' ';
    node = node->right;
  }
};

template <typename T> void postOrderTraversal(TreeNode<T> *const root) {
  std::stack<std::pair<TreeNode<T> *, bool>> traverseStack;
  traverseStack.push({root, false});
  while (!traverseStack.empty()) {
    TreeNode<T> *const node = traverseStack.top().first;
    bool isVisited = traverseStack.top().second;
    traverseStack.pop();

    if (node) {
      if (isVisited) {
        cout << node->data << ' ';
        continue;
      }
      traverseStack.push({node, true});
      traverseStack.push({node->right, false});
      traverseStack.push({node->left, false});
    }
  }
};

template <typename T> void layerOrderTraversal(TreeNode<T> *const root) {
  std::queue<TreeNode<T> *> traverseQueue;
  traverseQueue.push(root);
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

} // namespace iterative

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
  recursive::preOrderTraversal(tree.root);
  cout.put('\n');
  recursive::inOrderTraversal(tree.root);
  cout.put('\n');
  recursive::postOrderTraversal(tree.root);
  cout.put('\n');

  iterative::preOrderTraversal(tree.root);
  cout.put('\n');
  iterative::inOrderTraversal(tree.root);
  cout.put('\n');
  iterative::postOrderTraversal(tree.root);
  cout.put('\n');
  iterative::layerOrderTraversal(tree.root);
  cout.put('\n');

  // TreeNode<int> *ptr = tree.root;
  // while (ptr) {
  //   cout << ptr->data << ' ';
  //   ptr = ptr->left;
  // }
  return 0;
}