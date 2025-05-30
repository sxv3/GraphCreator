#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
using namespace std;

struct edge {
  int toIndex;
  int weight;
  edge* next;
};

struct node {
  char label[20];
  edge* head;

  node(const char* label);
  ~node();
};

class graph {
private:
  vector<node*> nodes;
  int getIndex(const char* label);

public:
  void addVertex(const char* label);
  void removeVertex(const char* label);

  void addEdge(const char* from, const char* to, int weight);
  void removeEdge(const char* from, const char* to);

  void printAdjacencyList();
   void shortestPath(const char* from, const char* to);
    ~graph();

};

#endif
