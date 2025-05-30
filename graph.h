#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

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
