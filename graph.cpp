#include "graph.h"
#include <iostream>
#include <cstring>

using namespace std;

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

void graph::addVertex(const char* name) {
  if (getIndex(lab) != -1) {
    cout << "vertex exists" << endl;
    return;
  }
  
  if (nodes.size() >= 20) {
    std::cout << "max vertice limit rearched";
    return;
  }
    
  node* newNode = new node(lab);
  nodes.push_back(newNode);
}

void graph::removeVertex(const char* name) {
  int index = getIndex(name);
  
  if (index == -1) {
    cout << "vertex not found" << endl;
    return;
  }
  
  for (int i = 0; i < nodes.size(); i++) {
    
    if (i != index) {
      edge* current = nodes[i]->head;
      edge* prevEdge = nullptr;
      
      while (current != nullptr) {
        if (current->toIndex == index) {
          
          edge* toDelete = current;
          
          if (prevEdge == nullptr) {
            nodes[i]->head = current->next;
          } else {
            prevEdge->next = current->next;
          }

          current = current->next;
          toDelete = NULL;
          delete toDelete;
        } else {
          
          prevEdge = current;
          current = current->next;
        }
      }
    }
  }
  
  delete nodes[index];
  nodes.erase(nodes.begin() + index);

  for (int i = 0; i < nodes.size(); i++) {
    edge* current = nodes[i]->head;
    
    while (current != nullptr) {
      
      if (current->toIndex > index) {
        current->toIndex--;
      }
      
      current = current->next;
    }
  }
}
