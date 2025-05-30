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
