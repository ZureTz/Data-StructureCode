#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <deque>
#include <initializer_list>
#include <iomanip>
#include <optional>
#include <ostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#define debug false

#if debug
#include <iostream>
#endif

struct HuffmanNode {
  using NodePtr = HuffmanNode *;

  NodePtr parent;
  NodePtr left, right;
  int frequencyCount;
  std::optional<char> element;

  HuffmanNode(int frequencyCount,
              std::optional<char> element = std::optional<char>())
      : parent(nullptr), left(nullptr), right(nullptr),
        frequencyCount(frequencyCount), element(element) {}
  ~HuffmanNode() {
    delete left;
    delete right;
  }
};

struct HuffmanTree {
  using NodePtr = HuffmanNode *;

  std::unordered_map<char, std::string> finalMap;
  NodePtr root = nullptr;

  HuffmanTree(const std::initializer_list<std::pair<char, int>> &list) {
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, NodePtrComp>
        queue;
    for (auto it = list.begin(); it != list.end(); ++it) {
      queue.push(new HuffmanNode(it->second, it->first));
    }

    while (queue.size() > 1) {
      const NodePtr node1 = queue.top();
      queue.pop();
      const NodePtr node2 = queue.top();
      queue.pop();
      NodePtr newNode =
          new HuffmanNode(node1->frequencyCount + node2->frequencyCount);
      newNode->left = node1, newNode->right = node2;
      node1->parent = node2->parent = newNode;
      queue.push(newNode);

#if debug
      std::cout << (node1->element.has_value() ? node1->element.value() : '#')
                << ',' << node1->frequencyCount << ' '
                << (node2->element.has_value() ? node2->element.value() : '#')
                << ',' << node2->frequencyCount << ' ';
      std::cout << (newNode->element.has_value() ? newNode->element.value()
                                                 : '#')
                << ',' << newNode->frequencyCount << std::endl;
#endif
    }
    root = queue.top();

    implementTreeInMap(root);
  }

  HuffmanTree(const std::string &sourceStr) {
    auto queue = getFrequencyQueue(sourceStr);
    while (queue.size() > 1) {
      const NodePtr node1 = queue.top();
      queue.pop();
      const NodePtr node2 = queue.top();
      queue.pop();

      const NodePtr newNode =
          new HuffmanNode(node1->frequencyCount + node2->frequencyCount);
      newNode->left = node1, newNode->right = node2;
      node1->parent = node2->parent = newNode;
      queue.push(newNode);

#if debug
      std::cout << (node1->element.has_value() ? node1->element.value() : '#')
                << ',' << node1->frequencyCount << ' '
                << (node2->element.has_value() ? node2->element.value() : '#')
                << ',' << node2->frequencyCount << ' ';
      std::cout << (newNode->element.has_value() ? newNode->element.value()
                                                 : '#')
                << ',' << newNode->frequencyCount << std::endl;
#endif
    }
    root = queue.top();

    implementTreeInMap(root);
  }

  void printFinalMap(std::ostream &os) const {
    for (auto it = finalMap.begin(); it != finalMap.end(); ++it) {
      os << '\'' << it->first << '\'' << " is aliased to: " << std::setw(15)
         << std::setfill(' ') << it->second
         << ", whose frequency is: " << std::setw(9) << std::setfill(' ')
         << getFrequency(it->first) << std::endl;
    }
  }

  int fullLength() const {
    int result = 0;
    for (auto it = finalMap.begin(); it != finalMap.end(); ++it) {
      result += it->second.size() * getFrequency(it->first);
    }
    return result;
  }

  int getFrequency(const char ch) const {
    if (finalMap.find(ch) == finalMap.end()) {
      return 0;
    }
    return getFrequencyByCode(root, finalMap.find(ch)->second);
  }
  ~HuffmanTree() { delete root; }

private:
  struct NodePtrComp {
    bool operator()(const HuffmanNode *const node1,
                    const HuffmanNode *const node2) const {
      if (node1->frequencyCount == node2->frequencyCount) {
        return node1->element > node2->element;
      }
      return node1->frequencyCount > node2->frequencyCount;
    }
  };

  std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, NodePtrComp>
  getFrequencyQueue(const std::string &sourceStr) {
    std::unordered_map<char, int> tempMap;
    for (const char ch : sourceStr) {
      tempMap[ch]++;
    }

    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, NodePtrComp>
        result;
    for (auto it = tempMap.begin(); it != tempMap.end(); ++it) {
      result.push(new HuffmanNode(it->second, it->first));
    }
    return result;
  }

  void implementTreeInMap(const NodePtr node, std::string pathString = "") {
    // Exit:
    if (node->element.has_value()) {
      finalMap.insert({node->element.value(), std::move(pathString)});
      return;
    }

    // Non-exit: expand string and pass to the next:
    if (node->left == nullptr) {
      throw "Left Child Not Found";
    }
    implementTreeInMap(node->left, std::move(pathString + "0"));

    if (node->right == nullptr) {
      throw "Right Child Not Found";
    }
    implementTreeInMap(node->right, std::move(pathString + "1"));
  }

  int getFrequencyByCode(NodePtr node, std::string code) const {
    if (code.empty()) {
      return node->frequencyCount;
    }
    const char front = code.front();
    code.erase(0, 1);
    switch (front) {
    case '0':
      return getFrequencyByCode(node->left, std::move(code));
    case '1':
      return getFrequencyByCode(node->right, std::move(code));
    default:
      return 0;
    }
  }
};

#endif