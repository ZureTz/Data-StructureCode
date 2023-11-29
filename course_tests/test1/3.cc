#include <iostream>
#include <list>
#include <sstream>
using std::cout;

namespace my {
template <typename T> class set {
public:
  std::list<T> list;

  set() {}
  set(const set &rhs) : list(rhs.list) {}
  set(set &&rhs) : list(rhs.list) {}
  ~set() {}

  void insert(T data) {
    for (const auto &element : list) {
      if (data == element) {
        return;
      }
    }
    list.push_back(data);
    list.sort();
  }

  void output() const {
    for (const auto &element : list) {
      cout << element;
    }
    cout.put('\n');
  }
};

template <typename T> set<T> AND(const set<T> &lhs, const set<T> &rhs) {
  my::set<T> result;
  auto it1 = lhs.list.begin(), it2 = rhs.list.begin();
  while (it1 != lhs.list.end() && it2 != rhs.list.end()) {
    if (*it1 < *it2) {
      it1++;
      continue;
    }
    if (*it1 > *it2) {
      it2++;
      continue;
    }

    // *it1 == *it2
    result.list.push_back(*it1);
    it1++, it2++;
  }

  return result;
}

template <typename T> set<T> OR(const set<T> &lhs, const set<T> &rhs) {
  my::set<T> result;
  auto it1 = lhs.list.begin(), it2 = rhs.list.begin();
  while (it1 != lhs.list.end() && it2 != rhs.list.end()) {
    if (*it1 < *it2) {
      result.list.push_back(*it1);
      it1++;
      continue;
    }
    if (*it1 > *it2) {
      result.list.push_back(*it2);
      it2++;
      continue;
    }

    // it1->exp == it2->exp
    result.list.push_back(*it1);
    it1++, it2++;
  }

  while (it1 != lhs.list.end()) {
    result.list.push_back(*it1);
    it1++;
  }

  while (it2 != rhs.list.end()) {
    result.list.push_back(*it2);
    it2++;
  }

  return result;
}

template <typename T> set<T> DIFF(const set<T> &lhs, const set<T> &rhs) {
  my::set<T> result;
  auto it1 = lhs.list.begin(), it2 = rhs.list.begin();

  while (it1 != lhs.list.end() && it2 != rhs.list.end()) {
    if (*it1 < *it2) {
      result.list.push_back(*it1);
      it1++;
      continue;
    }
    if (*it1 > *it2) {
      it2++;
      continue;
    }

    // *it1 == *it2
    it1++, it2++;
  }

  while (it1 != lhs.list.end()) {
    result.list.push_back(*it1);
    it1++;
  }

  return result;
}

} // namespace my

int main(int argc, char const *argv[]) {
  my::set<char> s1;
  while (std::cin.good() && std::cin.peek() != '\n') {
    char element;
    std::cin >> element;
    s1.insert(element);
  }
  std::cin.ignore();

  my::set<char> s2;
  while (std::cin.good() && std::cin.peek() != '\n') {
    char element;
    std::cin >> element;
    s2.insert(element);
  }
  std::cin.ignore();

  my::set<char> ORRes = my::OR(s1, s2);
  ORRes.output();
  my::set<char> ANDRes = my::AND(s1, s2);
  ANDRes.output();
  my::set<char> DIFFRes = my::DIFF(s1, s2);
  DIFFRes.output();

  return 0;
}