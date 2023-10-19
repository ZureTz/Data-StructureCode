#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>
using std::cin;
using std::cout;

template <typename T> struct OLNode {
  using OLink = OLNode<T> *;

  int i, j; // index
  T element;
  OLink right, down;

  OLNode<T>(int i, int j, T element, OLink right = nullptr,
            OLink down = nullptr)
      : i(i), j(j), element(element), right(right), down(down) {}
};

template <typename T> struct XList {
  using OLink = OLNode<T> *;

  OLink *rowHead, *colHead;
  int m, n, elementCount;

  XList<T>(int m, int n) : m(m), n(n) {
    rowHead = new OLink[m];
    for (int i = 0; i < m; ++i) {
      rowHead[i] = new OLNode<T>(0, 0, T());
    }
    colHead = new OLink[n];
    for (int i = 0; i < n; ++i) {
      colHead[i] = new OLNode<T>(0, 0, T());
    }
    elementCount = 0;
  }
  XList<T>(const std::vector<std::vector<T>> &src) {
    m = src.size();
    n = src.front().size();
    rowHead = new OLink[m];
    for (int i = 0; i < m; ++i) {
      rowHead[i] = new OLNode<T>(0, 0, T());
    }
    colHead = new OLink[n];
    for (int i = 0; i < n; ++i) {
      colHead[i] = new OLNode<T>(0, 0, T());
    }

    elementCount = 0;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (!src[i][j]) {
          continue;
        }
        OLink const newNode = new OLNode<T>(i, j, src[i][j]);
        elementCount++;

        OLink rowtemp = rowHead[i];
        while (rowtemp && rowtemp->right) {
          rowtemp = rowtemp->right;
        }
        rowtemp->right = newNode;

        OLink coltemp = colHead[j];
        while (coltemp && coltemp->down) {
          coltemp = coltemp->down;
        }
        coltemp->down = newNode;
      }
    }
  }
};

template <typename T> void add(XList<T> &lhs, const XList<T> &rhs) {
  using OLink = OLNode<T> *;

  if (!(lhs.m == rhs.m && lhs.n == rhs.n)) {
    std::cerr << "Invalid size" << std::endl;
    exit(EXIT_FAILURE);
  }

  const int m = lhs.m, n = lhs.n;
  if (rhs.elementCount == 0) {
    return;
  }

  for (int i = 0; i < m; ++i) {
    OLink p1 = lhs.rowHead[i];
    OLink p2 = rhs.rowHead[i];

    while (p1->right && p2->right) {
      if (p1->right->j == p2->right->j) {
        const int result = p1->right->element + p2->right->element;
        if (!result) {
          p1->right = p1->right->right;
          p2 = p2->right;
          continue;
        }
        p1->right->element = result;
        p1 = p1->right;
        p2 = p2->right;
        continue;
      }
      if (p1->right->j < p2->right->j) {
        OLink const newPtr = new OLNode<T>(i, p2->right->j, p2->right->element,
                                           p1->right->right);
        p1->right->right = newPtr;
        OLink temp = lhs.colHead[p2->right->j];
        while (temp->down && temp->down->i < i) {
          temp = temp->down;
        }
        newPtr->down = temp->down;
        temp->down = newPtr;

        p1 = p1->right;
        p2 = p2->right;
        continue;
      }
      if (p1->right->j > p2->right->j) {
        OLink const newPtr =
            new OLNode<T>(i, p2->right->j, p2->right->element, p1->right);
        p1->right = newPtr;

        OLink temp = lhs.colHead[p2->right->j];
        while (temp->down && temp->down->i < i) {
          temp = temp->down;
        }
        newPtr->down = temp->down;
        temp->down = newPtr;

        p1 = p1->right;
        p2 = p2->right;
        continue;
      }
    }
    if (p1->right == nullptr && p2->right) {
      while (p2->right) {
        OLink const newPtr =
            new OLNode<T>(i, p2->right->j, p2->right->element, p1->right);
        p1->right = newPtr;
        OLink temp = lhs.colHead[p2->right->j];
        while (temp->down && temp->down->i < i) {
          temp = temp->down;
        }
        newPtr->down = temp->down;
        temp->down = newPtr;
        p1 = p1->right;
        p2 = p2->right;
      }
      // OLink const newPtr = new OLNode<T>(i, p2->j, p2->element, p1->right);
      // p1->right = newPtr;
      // OLink temp = lhs.colHead[p2->j];
      // while (temp->down && temp->down->i < i) {
      //   temp = temp->down;
      // }
      // newPtr->down = temp->down;
      // temp->down = newPtr;
      continue;
    }
  }
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const XList<T> &src) {
  for (int i = 0; i < src.m; ++i) {
    auto temp = src.rowHead[i]->right;
    int prev = -1;
    while (temp) {
      const int diff = temp->j - prev - 1;
      for (int j = 0; j < diff; ++j) {
        os << "0 ";
      }
      os << temp->element << ' ';
      prev = temp->j;
      temp = temp->right;
    }
    const int diff = src.n - prev - 1;
    for (int j = 0; j < diff; ++j) {
      os << "0 ";
    }
    os << std::endl;
  }
  return os;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  XList<int> test({
      {1, 2, 0, 0, 0},
      {4, 0, 3, 0, 6},
      {0, 8, 2, 0, 0},
  });
  XList<int> test2({
      {1, 0, 0, 2, 0},
      {4, 4, 3, 0, 6},
      {0, 8, 2, 9, 0},
  });
  add(test, test2);
  cout << test;
  return 0;
}