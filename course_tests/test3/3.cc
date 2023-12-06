#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <limits>
using std::cout;

constexpr unsigned long long maxSize = 500500;

char sourceStr[maxSize];
int resTree[maxSize][3], size[maxSize];
int f[maxSize][3], g[maxSize][3];
int index = 0;

void buildTree(const int root) {
  size[root] = sourceStr[root] - '0';

  if (sourceStr[root] >= '1') {
    resTree[root][0] = ++index;
    buildTree(index);
  }
  if (sourceStr[root] == '2') {
    resTree[root][1] = ++index;
    buildTree(index);
  }
}

void Process(const int x) {
  if (size[x] == 0) {
    f[x][2] = g[x][2] = 1;
    return;
  }

  for (int i = 0; i < size[x]; ++i) {
    Process(resTree[x][i]);
  }

  for (int i = 0; i <= 2; ++i) {
    int colorOne = (i + 1) % 3, colorTwo = (i + 2) % 3;
    int leftSon = resTree[x][0], rightSon = resTree[x][1];
    if (size[x] == 1) {
      f[x][i] = std::max(f[leftSon][colorOne], f[leftSon][colorTwo]);
      g[x][i] = std::min(g[leftSon][colorOne], g[leftSon][colorTwo]);
    }
    if (size[x] == 2) {
      f[x][i] = std::max(f[leftSon][colorOne] + f[rightSon][colorTwo],
                         f[leftSon][colorTwo] + f[rightSon][colorOne]);
      g[x][i] = std::min(g[leftSon][colorOne] + g[rightSon][colorTwo],
                         g[leftSon][colorTwo] + g[rightSon][colorOne]);
    }
    if (i == 2) {
      f[x][i]++, g[x][i]++;
    }
  }
}

int main(int argc, char const *argv[]) {

  auto initialize = []() {
    scanf("%s", (sourceStr + 1));
    index = 1;
    buildTree(index);
  };
  initialize();
  Process(1);

  auto output = [](std::ostream&os) {
    int maximum = 0, minimum = std::numeric_limits<int>::max();
    for (int i = 0; i <= 2; ++i) {
      maximum = std::max(maximum, f[1][i]);
      minimum = std::min(minimum, g[1][i]);
    }
    os << maximum << ' ' << minimum <<'\n';
  };
  output(cout);

  return 0;
}