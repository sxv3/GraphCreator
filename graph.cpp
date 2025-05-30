#include "graph.h"
#include <iostream>
#include <cstring>

node::node(const char* name) {
  strncpy(label, name, 19);
  label[19] = '\0';
  head = nullptr;
}

node::~node() {
  edge* current = head;
  
  while (current != nullptr) {
    
    edge* nextEdge = current->next;
    current = NULL;
    
    delete current;
    current = nextEdge;
  }
}

graph::~graph() {
  for (int i = 0; i < nodes.size(); i++) {
    nodes[i] = NULL;    
    delete nodes[i];
  }
  
  nodes.clear();
}

int graph::getIndex(const char* name) {
  for (int i = 0; i < nodes.size(); i++) {
    if (strcmp(nodes[i]->label, name) == 0) {
      return i;
      }
  }
  
  return -1;
}
