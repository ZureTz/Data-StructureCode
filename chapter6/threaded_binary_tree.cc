#include <initializer_list>
#include <iostream>
#include <queue>
using std::cout;

template <typename T> struct ThreadedTreeNode {
  using NodePtr = ThreadedTreeNode<T> *;

  T data;
  NodePtr left;
  NodePtr right;

  enum Tag { Link, Threaded };
  Tag leftTag = Tag::Link, rightTag = Tag::Link;

  ThreadedTreeNode<T>(T data = T(), NodePtr left = nullptr,
                      NodePtr right = nullptr)
      : data(data), left(left), leftTag(Link), right(right), rightTag(Link) {}
};

template <typename T> struct ThreadedTree {
  using NodePtr = ThreadedTreeNode<T> *;

  NodePtr const root;

  ThreadedTree<T>(const std::initializer_list<T> &list)
      : root(new ThreadedTreeNode<T>(*list.begin())) {

    std::queue<NodePtr> insertQueue;
    insertQueue.push(root);

    auto it = list.begin() + 1;
    while (it != list.end()) {
      NodePtr tempPtr = insertQueue.front();
      insertQueue.pop();

      tempPtr->left = new ThreadedTreeNode<T>(*it++);
      insertQueue.push(tempPtr->left);
      if (it == list.end()) {
        break;
      }

      tempPtr->right = new ThreadedTreeNode<T>(*it++);
      insertQueue.push(tempPtr->right);
    }

    NodePtr prev = nullptr;
    threadTreeImpl(root, prev);
  }

  void threadTreeImpl(NodePtr root, NodePtr &prev) {
    if (root == nullptr) {
      return;
    }
    threadTreeImpl(root->left, prev);
    if (root->left == nullptr) {
      root->left = prev;
      root->leftTag = ThreadedTreeNode<T>::Threaded;
    }
    if (prev && prev->right == nullptr) {
      prev->right = root;
    }
    if (root->right == nullptr) {
      root->rightTag = ThreadedTreeNode<T>::Threaded;
    }
    prev = root;
    threadTreeImpl(root->right, prev);
  }
};

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
  ThreadedTree<int> tree{
      2, 3, 5, 7, 11, 13, 15, 24, 4, 5, 6,
  };
  cout << tree.root->left->left->left->left << ' '
       << (tree.root->left->left->left->leftTag == ThreadedTreeNode<int>::Threaded
               ? "Threaded"
               : "Linked");
  return 0;
}