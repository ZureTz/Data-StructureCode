#include <algorithm>
#include <cstddef>
#include <deque>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using std::cout;

struct pairHash {
  std::size_t operator()(const std::pair<int, int> &pair) const {
    return std::hash<int>()(pair.first) ^ (std::hash<int>()(pair.second) << 1);
  }
};

void DFS(std::deque<int> &dest,
         const std::vector<std::vector<std::pair<int, int>>> &adjList,
         std::vector<bool> &isVisited, int node) {
  if (isVisited[node]) {
    return;
  }
  isVisited[node] = true;
  for (int i = adjList[node].size() - 1; i >= 0; --i) {
    DFS(dest, adjList, isVisited, adjList[node][i].first);
  }
  dest.push_front(node);
}

void topoSort(std::deque<int> &dest,
              const std::vector<std::vector<std::pair<int, int>>> &adjList) {
  std::vector<bool> isVisited(adjList.size(), false);
  for (int i = adjList.size()- 1; i >= 0; --i) {
    DFS(dest, adjList, isVisited, i);
  }
}

int main(int argc, char const *argv[]) {

  int numVertecies, numEdges;
  (std::cin >> numVertecies >> numEdges).get();

  std::unordered_map<std::string, int> inputVerteciesAlias;
  std::unordered_map<int, std::string> outputVerteciesAlias;
  for (int i = 0; i < numVertecies; ++i) {
    std::string tempStr;
    std::cin >> tempStr;
    outputVerteciesAlias[i] = tempStr;
    inputVerteciesAlias[tempStr] = i;
  }

  std::unordered_map<std::pair<int, int>, std::string, pairHash> edgesAlias;

  // index, length
  std::vector<std::vector<std::pair<int, int>>> adjList(numVertecies);
  std::vector<std::vector<std::pair<int, int>>> revAdjList(numVertecies);
  std::vector<std::pair<std::pair<int, int>, int>> edges(numEdges);

  for (int i = 0; i < numEdges; ++i) {
    std::string src, dest, edgeName;
    std::cin >> src >> dest >> edgeName;
    int length;
    std::cin >> length;

    const int srcIndex = inputVerteciesAlias[src],
              destIndex = inputVerteciesAlias[dest];

    adjList[srcIndex].push_back({destIndex, length});
    revAdjList[destIndex].push_back({srcIndex, length});

    edgesAlias[{srcIndex, destIndex}] = edgeName;
    edges[i] = {{srcIndex, destIndex}, length};
  }

  // debugging
  // for (const auto &pair : inputVerteciesAlias) {
  //   cout << pair.first << ", " << pair.second << '\n';
  // }
  // for (const auto &pair : outputVerteciesAlias) {
  //   cout << pair.first << ", " << pair.second << '\n';
  // }
  // for (const auto &pair : edgesAlias) {
  //   cout << pair.first.first << ' ' << pair.first.second << ", " <<
  //   pair.second
  //        << '\n';
  // }
  // for (int i = 0; i < numVertecies; ++i) {
  //   cout << i << ": ";
  //   for (const auto &adjVer : adjList[i]) {
  //     cout << '[' << adjVer.first << ", " << adjVer.second << ']' << ' ';
  //   }
  //   cout << std::endl;
  // }
  // for (int i = 0; i < numVertecies; ++i) {
  //   cout << i << ": ";
  //   for (const auto &revAdjVer : revAdjList[i]) {
  //     cout << '[' << revAdjVer.first << ", " << revAdjVer.second << ']' << '
  //     ';
  //   }
  //   cout << std::endl;
  // }
  // for (const auto &pair : edges) {
  //   cout << pair.first.first << ' ' << pair.first.second << ", " <<
  //   pair.second
  //        << '\n';
  // }

  // topoSort and revTopoSort
  std::deque<int> topoResult;
  topoSort(topoResult, adjList);
  std::deque<int> revTopoResult;
  topoSort(revTopoResult, revAdjList);
  // 1: output toposort order
  for (const int vertex : topoResult) {
    cout << outputVerteciesAlias[vertex] << ' ';
  }
  cout << '\n';

  // for (const int vertex : topoResult) {
  //   cout << vertex << ' ';
  // }
  // cout << std::endl;
  // for (const int vertex : revTopoResult) {
  //   cout << vertex << ' ';
  // }
  // cout << std::endl;

  // ve, vl calculation
  std::vector<int> ve(numVertecies), vl(numVertecies);
  for (const int vertex : topoResult) {
    int max = 0;
    for (const auto &src : revAdjList[vertex]) {
      max = std::max(max, ve[src.first] + src.second);
    }
    ve[vertex] = max;
  }
  // for (const int veNum : ve) {
  //   cout << veNum << ' ';
  // }
  // cout << std::endl;

  const int minmumTime = vl[revTopoResult.front()] = ve[topoResult.back()];
  for (const int vertex : revTopoResult) {
    int min = ve[topoResult.back()];
    for (const auto &dest : adjList[vertex]) {
      min = std::min(min, vl[dest.first] - dest.second);
    }
    vl[vertex] = min;
  }
  // for (const int veNum : vl) {
  //   cout << veNum << ' ';
  // }
  // cout << std::endl;

  // e, l for edges
  std::vector<int> e(numEdges), l(numEdges);
  for (int i = 0; i < numEdges; ++i) {
    e[i] = ve[edges[i].first.first];
    l[i] = vl[edges[i].first.second] - edges[i].second;
  }

  // 2: output ciritcal path
  for (int i = 0; i < numEdges; ++i) {
    if (l[i] - e[i] == 0) {
      cout << outputVerteciesAlias[edges[i].first.first] << ' '
           << outputVerteciesAlias[edges[i].first.second] << '\n';
    }
  }

  // 3: output ve and vl
  for (int i = 0; i < numEdges; ++i) {
    cout << edgesAlias[edges[i].first] << ' ' << e[i] << ' ' << l[i] << '\n';
  }

  // 4: output critical acticity
  cout << minmumTime << '\n';
  for (int i = 0; i < numEdges; ++i) {
    if (l[i] - e[i] == 0) {
      cout << edgesAlias[edges[i].first] << ' ';
    }
  }
  cout << '\n';

  return 0;
}