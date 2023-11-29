#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <list>
using std::cin;
using std::cout;

struct Node {
  int coef;
  int exp;
  Node(int coef, int exp) : coef(coef), exp(exp) {}
};

std::list<Node> mergeList(const std::list<Node> &l1,
                          const std::list<Node> &l2) {
  std::list<Node> result;

  auto it1 = l1.begin(), it2 = l2.begin();
  while (it1 != l1.end() && it2 != l2.end()) {
    if (it1->exp > it2->exp) {
      result.push_back(*it1);
      it1++;
      continue;
    }
    if (it1->exp < it2->exp) {
      result.push_back(*it2);
      it2++;
      continue;
    }

    // it1->exp == it2->exp
    if (it1->coef + it2->coef == 0) {
      it1++, it2++;
      continue;
    }
    result.emplace_back(it1->coef + it2->coef, it1->exp);
    it1++, it2++;
  }

  while (it1 != l1.end()) {
    result.push_back(*it1);
    it1++;
  }

  while (it2 != l2.end()) {
    result.push_back(*it2);
    it2++;
  }

  return result;
}

int main(int argc, char const *argv[]) {

  int list1Length, list2Length;
  cin >> list1Length >> list2Length;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::list<Node> list1;
  for (int i = 0; i < list1Length; ++i) {
    int coef, exp;
    char eater;
    cin >> coef >> exp >> eater;
    list1.push_back(Node(coef, exp));
  }

  std::list<Node> list2;
  for (int i = 0; i < list2Length; ++i) {
    int coef, exp;
    char eater;
    cin >> coef >> exp >> eater;
    list2.push_back(Node(coef, exp));
  }

  auto NodeComp = [](const Node &n1, const Node &n2) {
    return n1.exp > n2.exp;
  };
  list1.sort(NodeComp);
  list2.sort(NodeComp);

  auto res = mergeList(list1, list2);
  for (const auto &node : res) {
    cout << node.coef << ' ' << node.exp << ',';
  }
  cout << "\b \n";

  return 0;
}