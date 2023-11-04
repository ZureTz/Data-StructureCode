#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

// Binary tree node
template <typename T> struct TreeNode {
  using NodePtr = TreeNode<T> *;

  T data;
  NodePtr left;
  NodePtr right;

  TreeNode<T>(T data = T(), NodePtr left = nullptr, NodePtr right = nullptr)
      : data(data), left(left), right(right) {}

  ~TreeNode<T>() {
    delete left;
    delete right;
  }
};

// Binary tree (contains a root pointer)
template <typename T> struct BinaryTree {
  using NodePtr = TreeNode<T> *;

  NodePtr root;

  BinaryTree<T>(const std::initializer_list<T> &list) {
    if (list.size() == 0) {
      root = nullptr;
      return;
    }
    root = new TreeNode<T>(*list.begin());

    std::stack<TreeNode<T> *> initializerStack;
    initializerStack.push(root);
    TreeNode<T> *node = root;

    auto it = list.begin() + 1;
    while (it < list.end()) {
      while (it < list.end() && *it != T()) {
        node->left = new TreeNode<T>(*it);
        node = node->left;
        initializerStack.push(node);
        ++it;
      }
      // *it == null
      // or: the iterator comes to the end of the list
      while (it < list.end() && !initializerStack.empty() && *it == T()) {
        node = initializerStack.top();
        initializerStack.pop();
        ++it;
      }
      if (it >= list.end()) {
        break;
      }
      if (*it == T() && initializerStack.empty()) {
        break;
      }
      node->right = new TreeNode<T>(*it);
      node = node->right;
      initializerStack.push(node);
      ++it;
    }
  }

  void preOrderTraversal(std::ostream &os) const {
    if (root == nullptr) {
      return;
    }

    std::function<void(TreeNode<T> *)> print =
        [&os, &print](TreeNode<T> *node) -> void {
      if (node == nullptr) {
        return;
      }
      os << node->data << ' ';
      print(node->left);
      print(node->right);
    };

    print(root);
  }

  void layerOrderTraversal(std::ostream &os) const {
    if (root == nullptr) {
      return;
    }
    std::queue<TreeNode<T> *> traverseQueue;
    traverseQueue.push(root);
    while (!traverseQueue.empty()) {
      const TreeNode<T> *node = traverseQueue.front();
      traverseQueue.pop();
      if (node == nullptr) {
        continue;
      }
      os << node->data << ' ';
      traverseQueue.push(node->left);
      traverseQueue.push(node->right);
    }
  }

  ~BinaryTree<T>() { delete root; }
};

// Threaded binary tree
enum PointerTag { Link, Threaded };
template <typename T> struct ThreadedTreeNode {
  using NodePtr = ThreadedTreeNode<T> *;

  T data;
  PointerTag leftTag, rightTag;
  NodePtr left, right;

  ThreadedTreeNode<T>(T data) : data(data) {
    leftTag = rightTag = PointerTag::Link;
    left = right = nullptr;
  }

  NodePtr priorNode() const {
    if (this->leftTag == PointerTag::Link) {
      NodePtr node = this->left;
      while (node->rightTag == PointerTag::Link) {
        node = node->right;
      }
      return node;
    }
    // else: the prior node is threaded
    return this->left;
  }

  NodePtr nextNode() const {
    if (this->rightTag == PointerTag::Link) {
      NodePtr node = this->right;
      while (node->leftTag == PointerTag::Link) {
        node = node->left;
      }
      return node;
    }
    // else: the next node is threaded
    return this->right;
  }

  ~ThreadedTreeNode<T>() {
    if (leftTag == PointerTag::Link) {
      delete left;
    }
    if (rightTag == PointerTag::Link) {
      delete right;
    }
  }
};

template <typename T> struct ThreadedBinaryTree {
  using NodePtr = ThreadedTreeNode<T> *;

  NodePtr root;

  ThreadedBinaryTree<T>(const BinaryTree<T> &sourceTree) {
    if (sourceTree.root == nullptr) {
      root = nullptr;
      return;
    }

    std::vector<NodePtr> inOrderResults;
    std::function<NodePtr(TreeNode<T> *)> copyAndPush =
        [&inOrderResults, &copyAndPush](TreeNode<T> *source) -> NodePtr {
      if (source == nullptr) {
        return nullptr;
      }
      NodePtr result = new ThreadedTreeNode<T>(source->data);
      result->left = copyAndPush(source->left);
      inOrderResults.push_back(result);
      result->right = copyAndPush(source->right);
      return result;
    };

    this->root = copyAndPush(sourceTree.root);

    if (inOrderResults.size() < 2) {
      this->root->leftTag = this->root->rightTag = PointerTag::Threaded;
      return;
    }

    NodePtr frontNode = inOrderResults.front();
    frontNode->leftTag = PointerTag::Threaded;
    if (frontNode->right == nullptr) {
      frontNode->rightTag = PointerTag::Threaded;
      frontNode->right = *(inOrderResults.begin() + 1);
    }
    for (auto it = inOrderResults.begin() + 1; it != inOrderResults.end() - 1;
         ++it) {
      NodePtr currentNode = (*it);
      if (currentNode->left == nullptr) {
        currentNode->leftTag = PointerTag::Threaded;
        currentNode->left = *(it - 1);
      }
      if (currentNode->right == nullptr) {
        currentNode->rightTag = PointerTag::Threaded;
        currentNode->right = *(it + 1);
      }
    }
    NodePtr backNode = inOrderResults.back();
    backNode->rightTag = PointerTag::Threaded;
    if (backNode->left == nullptr) {
      backNode->leftTag = PointerTag::Threaded;
      backNode->left = *(inOrderResults.end() - 2);
    }
  }

  void preOrderTraversal(std::ostream &os) const {
    if (root == nullptr) {
      return;
    }

    NodePtr node = root;
    while (node) {
      os << node->data << ' ';
      if (node->leftTag == PointerTag::Link) {
        node = node->left;
        continue;
      }
      if (node->rightTag == PointerTag::Link) {
        node = node->right;
        continue;
      }
      while (node && node->rightTag == PointerTag::Threaded) {
        node = node->right;
      }
      if (node) {
        node = node->right;
      }
    }
  }

  ~ThreadedBinaryTree<T>() { delete root; }
};

#endif