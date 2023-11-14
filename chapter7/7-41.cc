#include "graph.h"
#include <algorithm>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace AdjacentList;

void printCriticalPath(const Graph &graph) {
  // step 1: compute the indegree foreach vertex
  std::vector<int> inDegree(graph.list.size(), 0);
  for (int i = 0; i < graph.list.size(); ++i) {
    EdgeNode *edge = graph.list[i]->firstEdge;
    while (edge) {
      inDegree[edge->pointTo]++;
      edge = edge->nextEdge;
    }
  }

  // step 2: topological sort
  std::queue<int> sortQueue;
  std::deque<int> topologicalOrder;
  for (int i = 0; i < graph.list.size(); ++i) {
    if (inDegree[i] == 0) {
      sortQueue.push(i);
    }
  }
  while (!sortQueue.empty()) {
    int index = sortQueue.front();
    sortQueue.pop();
    topologicalOrder.push_back(index);

    EdgeNode *edge = graph.list[index]->firstEdge;
    while (edge) {
      inDegree[edge->pointTo]--;
      if (inDegree[edge->pointTo] == 0) {
        sortQueue.push(edge->pointTo);
      }
      edge = edge->nextEdge;
    }
  }

  // step 3: compute the earliest start time for each vertex
  std::vector<int> earliestStartTime(graph.list.size(), 0);
  for (const int vertexIndex : topologicalOrder) {
    EdgeNode *edge = graph.list[vertexIndex]->firstEdge;
    while (edge) {
      int dest = edge->pointTo;
      int weight = edge->edgeLength;
      earliestStartTime[dest] = std::max(
          earliestStartTime[dest], earliestStartTime[vertexIndex] + weight);

      edge = edge->nextEdge;
    }
  }
  for (int i = 0; i < graph.list.size(); ++i) {
    std::cout << earliestStartTime[i] << ' ';
  }
  std::cout << std::endl;

  // step 4: compute the latest start time for each vertex
  std::vector<int> latestStartTime(graph.list.size(),
                                   std::numeric_limits<int>::max());
  latestStartTime[topologicalOrder[graph.list.size() - 1]] =
      earliestStartTime[topologicalOrder[graph.list.size() - 1]];
  for (int i = graph.list.size() - 2; i >= 0; --i) {
    int vertex = topologicalOrder[i];
    EdgeNode *edge = graph.list[vertex]->firstEdge;
    while (edge) {
      int dest = edge->pointTo;
      int weight = edge->edgeLength;
      latestStartTime[vertex] =
          std::min(latestStartTime[vertex], latestStartTime[dest] - weight);
          
      edge = edge->nextEdge;
    }
  }
  for (int i = 0; i < graph.list.size(); ++i) {
    std::cout << latestStartTime[i] << ' ';
  }
  std::cout << std::endl;

  // step 5: compute slack
  std::vector<int> slack(graph.list.size());
  for (int i = 0; i < graph.list.size(); ++i) {
    slack[i] = latestStartTime[i] - earliestStartTime[i];
    std::cout << slack[i] << ' ';
  }
  std::cout << std::endl;

  // step 6: print critical path
  std::cout << "Critical Path: ";
  EdgeNode *edge = graph.list[topologicalOrder[0]]->firstEdge;
  std::cout << graph.list[topologicalOrder[0]]->data << ' ';
  while (edge) {
    if (slack[edge->pointTo] == 0) {
      std::cout << graph.list[edge->pointTo]->data << ' ';
      edge = graph.list[edge->pointTo]->firstEdge;
      continue;
    }
    edge = edge->nextEdge;
  }
  std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
  // Example: Project Management - Critical Path Analysis
  // Given a project with multiple tasks and their dependencies, we can use
  // the critical path algorithm to determine the longest path and identify
  // the critical tasks that must be completed on time.
  {
    Graph project; // Represents a project with 7 tasks
    for (int i = 0; i < 9; ++i) {
      project.vertexPush(i);
    }

    // Adding directed edges between tasks with their respective durations
    project.edgeConnect(0, 1, 0); 
    project.edgeConnect(0, 2, 0); 
    project.edgeConnect(1, 2, 7); 
    project.edgeConnect(1, 3, 7); 
    project.edgeConnect(3, 6, 12); 
    project.edgeConnect(4, 5, 8); 
    project.edgeConnect(5, 6, 9); 
    project.edgeConnect(5, 7, 9); 
    project.edgeConnect(6, 8, 6); 
    project.edgeConnect(7, 8, 5); 



    printCriticalPath(project);

    // int longestPathDuration = project.criticalPath();
    // std::cout << "Longest Path Duration: " << longestPathDuration
    // << " units.\n";
  }
  return 0;
}