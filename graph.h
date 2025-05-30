#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
using namespace std;

//graph header file
//by Tai Wong, 5/29/25

//edge struct
struct edge {
  int toIndex;
  int weight;
  edge* next;
};

//node struct
struct node {
  char label[20];
  edge* head;

  node(const char* name);
  ~node();
};

//graph class
class graph {
private:
//vector of nodess
  vector<node*> nodes;
  int getIndex(const char* name);

public:
//functions
  void addVertex(const char* name);
  void removeVertex(const char* name);

  void addEdge(const char* from, const char* to, int weight);
  void removeEdge(const char* from, const char* to);

  void printAdjacencyList();
  void shortestPath(const char* from, const char* to);
  ~graph();

};

#endif
