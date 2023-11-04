#include <iostream>
#include "binary_tree.h"
using std::cout;

template <typename T> struct Null {
  inline T operator()(void) const { return T(); }
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  /*
   *                  +--+
   *                  |30|
   *            +------------------+
   *            |                  |
   *         +--+                 ++-+
   *         |15|                 |35|
   *    +------------+         +----------+
   *    |            |       +--+       +--+
   *  +-+          +-++      |32|       |38|
   *  |4|          |20|      +--+       +--+
   *  +-+          +--+
   *         +-----+
   *         |18|
   *         +---+
   *             |
   *             +----+
   *               |19|
   *               +--+
   */
  BinaryTree<int> tree{
      30,
      15,
      4,
      Null<int>()(),
      Null<int>()(),
      20,
      18,
      Null<int>()(),
      19,
      Null<int>()(),
      Null<int>()(),
      Null<int>()(),
      35,
      32,
      Null<int>()(),
      Null<int>()(),
      38,
      Null<int>()(),
      Null<int>()(),
  };

  tree.layerOrderTraversal(cout);
  cout.put('\n');

  ThreadedBinaryTree<int> Threaded(tree);
  ThreadedTreeNode<int> *node = Threaded.root->left->right;
  cout << (node->priorNode() ? node->priorNode()->data : 0) << ' '
       << (node->nextNode() ? node->nextNode()->data : 0) << std::endl;
  
  return 0;
}