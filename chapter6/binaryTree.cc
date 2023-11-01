#include "binary_tree.h"
#include <_types/_uint32_t.h>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
using std::cout;

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
  recursive::preOrderTraversalVer2(tree.root);
  return 0;
}