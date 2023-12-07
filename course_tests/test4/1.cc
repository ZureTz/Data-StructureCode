#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
using std::cout;

#if true
#include <deque>
#include <iomanip>
#endif

struct TreeNode {
  int data;
  TreeNode *left, *right;

  TreeNode(int data, TreeNode *left = nullptr, TreeNode *right = nullptr)
      : data(data), left(left), right(right) {}
};

void buildTree(TreeNode *root, const std::vector<int> &data, int index) {
  if (root == nullptr || index >= data.size()) {
    return;
  }
  const int currentNum = data[index];

  if (currentNum < root->data) {
    if (root->left == nullptr) {
      root->left = new TreeNode(currentNum);
      return;
    }
    buildTree(root->left, data, index);
    return;
  }

  // if (currentNum >= root->data)
  if (root->right == nullptr) {
    root->right = new TreeNode(currentNum);
    return;
  }

  buildTree(root->right, data, index);
}

std::size_t getHeight(TreeNode *const root) {
  if (root == nullptr) {
    return 0ull;
  }
  return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

bool isTreeBalanced(TreeNode *const root) {
  if (root == nullptr) {
    return true;
  }
  const bool leftBalanced = isTreeBalanced(root->left);
  const bool rightBalanced = isTreeBalanced(root->right);
  if (!leftBalanced or !rightBalanced) {
    return false;
  }

  const int leftHeight = getHeight(root->left);
  const int rightHeight = getHeight(root->right);
  if (abs(leftHeight - rightHeight) > 1) {
    return false;
  }
  return true;
}

std::deque<std::deque<int>> treeTable(TreeNode *root, const size_t height,
                                    const size_t currentIndex = 0) {
  if (root == nullptr) {
    return std::deque<std::deque<int>>();
  }

  std::deque<std::deque<int>> leftResult =
      treeTable(root->left, height, currentIndex + 1);

  std::deque<std::deque<int>> result(1, std::deque<int>(height, int()));
  result[0][currentIndex] = root->data;

  std::deque<std::deque<int>> rightResult =
      treeTable(root->right, height, currentIndex + 1);

  result.insert(result.begin(), rightResult.begin(), rightResult.end());
  result.insert(result.end(), leftResult.begin(), leftResult.end());

  return result;
}

 void printTreeAsTable(TreeNode *root) {
  if (root == nullptr) {
    return;
  }
  const size_t height = getHeight(root);
  const auto result = treeTable(root, height);
  for (const auto row : result) {
    for (const int data : row) {
      if (data == int()) {
        cout << std::setw(5) << std::setfill(' ') << ' ' << " ";
        continue;
      }
      cout << std::setw(5) << std::setfill(' ') << data << " ";
    }
    cout << '\n';
  }
}

int main(int argc, char const *argv[]) {

  int numOfNodes;
  std::cin >> numOfNodes;

  std::vector<int> data(numOfNodes);
  for (auto &num : data) {
    std::cin >> num;
  }

  if (data.size() == 0) {
    cout << "true" << '\n';
    return 0;
  }

  TreeNode *const root = new TreeNode(data.front());
  for (int i = 1; i < data.size(); ++i) {
    buildTree(root, data, i);
  }

  // printTreeAsTable(root);

  cout << (isTreeBalanced(root) ? "true" : "false") << '\n';

  return 0;
}