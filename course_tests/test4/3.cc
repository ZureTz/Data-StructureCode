#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using std::cout;

struct HuffmanNode {
  using NodePtr = HuffmanNode *;

  NodePtr parent;
  NodePtr left, right;
  int frequencyCount;

  HuffmanNode(int frequencyCount)
      : parent(nullptr), left(nullptr), right(nullptr),
        frequencyCount(frequencyCount) {}
  ~HuffmanNode() {
    delete left;
    delete right;
  }
};

struct nodeCmp {
  bool operator()(HuffmanNode *const node1, HuffmanNode *const node2) const {
    return node1->frequencyCount > node2->frequencyCount;
  }
};

int getWPL(HuffmanNode*const root) {
  if (root == nullptr) {
    return 0;
  }
  if (root->left == nullptr && root->right == nullptr) {
    return 0;
  }
  return root->frequencyCount + getWPL(root->left) + getWPL(root->right);
}

int main(int argc, char const *argv[]) {

  int numOfNodes;
  std::cin >> numOfNodes;

  std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, nodeCmp> pq;
  for (int i = 0; i < numOfNodes; ++i) {
    int tempFrec;
    std::cin >> tempFrec;
    pq.push(new HuffmanNode(tempFrec));
  }

  while (pq.size() > 1) {
    HuffmanNode *const node1 = pq.top();
    pq.pop();
    HuffmanNode *const node2 = pq.top();
    pq.pop();
    const auto newNode =
        new HuffmanNode(node1->frequencyCount + node2->frequencyCount);
    newNode->left = node1, newNode->right = node2;
    pq.push(newNode);
  }
  HuffmanNode *root = pq.top();

  cout << getWPL(root) << '\n';

  return 0;
}