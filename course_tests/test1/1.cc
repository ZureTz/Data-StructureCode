#include <cctype>
#include <iostream>
#include <limits>
#include <list>
#include <sstream>
#include <string>
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
  std::cin >> list1Length >> list2Length;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::list<Node> list1;
  std::string t2;
  std::getline(cin, t2);
  std::stringstream ss2(t2);
  for (int i = 0; i < list1Length; ++i) {
    int coef, exp;
    while (!isdigit(ss2.peek()) && !(ss2.peek() == '-')) {
      ss2.get();
    }
    ss2 >> coef;

    while (!isdigit(ss2.peek()) && !(ss2.peek() == '-')) {
      ss2.get();
    }
    ss2 >> exp;
    if (coef == 0) {
      continue;
    }
    list1.push_back(Node(coef, exp));
  }

  // for (const auto &node : list1) {
  //   cout << node.coef << ' ' << node.exp << ',';
  // }
  // cout << "\b \n";

  std::list<Node> list2;
  std::string t1;
  std::getline(cin, t1);
  std::stringstream ss1(t1);
  for (int i = 0; i < list2Length; ++i) {
    int coef, exp;
    while (!isdigit(ss1.peek()) && !(ss1.peek() == '-')) {
      ss1.get();
    }
    ss1 >> coef;

    while (!isdigit(ss1.peek()) && !(ss1.peek() == '-')) {
      ss1.get();
    }
    ss1 >> exp;
    if (coef == 0) {
      continue;
    }
    list2.push_back(Node(coef, exp));
  }

  // for (const auto &node : list2) {
  //   cout << node.coef << ' ' << node.exp << ',';
  // }
  // cout << "\b \n";

  auto NodeComp = [](const Node &n1, const Node &n2) {
    return n1.exp > n2.exp;
  };
  list1.sort(NodeComp);
  list2.sort(NodeComp);

  auto res = mergeList(list1, list2);
  if (res.empty()) {
    cout << "0 0";
    return 0;
  }
  // for (const auto &node : res) {
  //   cout << node.coef;
  //   if (node.exp) {
  //     cout << ' ' << node.exp;
  //   }
  //   cout << ',';
  // }
  // cout << "\b ";
  auto it = res.begin();
  cout << it->coef << ' ' << it->exp;
  ++it;
  while (it != res.end()) {
    cout << ',' << it->coef << ' ' << it->exp;
    ++it;
  }
  cout << std::endl;

  return 0;
}