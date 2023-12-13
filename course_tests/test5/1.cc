#include <iostream>
#include <vector>
using std::cout;

void DFS(const std::vector<std::vector<int>> &adjList, std::vector<int> &stack,
         std::vector<bool> &isVisited, int beginNode) {
  if (isVisited[beginNode]) {
    return;
  }

  if (stack.size() == adjList.size()) {
    for (const int vertex : stack) {
      cout << vertex + 1 << ' ';
    }
    cout << std::endl;
    return;
  }

  isVisited[beginNode] = true;

  for (const int adjVertex : adjList[beginNode]) {
    stack.push_back(adjVertex);
    DFS(adjList, stack, isVisited, adjVertex);
    stack.pop_back();
  }
  isVisited[beginNode] = false;
}

int main(int argc, char const *argv[]) {

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> adjList(n);
  std::vector<bool> isVisited(n, false);
  std::vector<int> stack;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int isConnected;
      std::cin >> isConnected;
      if (isConnected) {
        adjList[i].push_back(j);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    stack.push_back(i);
    DFS(adjList, stack, isVisited, i);
    stack.pop_back();
  }

  return 0;
}