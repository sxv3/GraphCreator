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
    current = nullptr;
    
    delete current;
    current = nextEdge;
  }
}

graph::~graph() {
  for (int i = 0; i < nodes.size(); i++) {
    nodes[i] = nullptr;    
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
  if (getIndex(name) != -1) {
    cout << "vertex exists" << endl;
    return;
  }
  
  if (nodes.size() >= 20) {
    std::cout << "max vertice limit rearched";
    return;
  }
    
  node* newNode = new node(name);
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
          toDelete = nullptr;
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

void graph::addEdge(const char* from, const char* to, int weight) {
  
  int fIndex = getIndex(from);
  int tIndex = getIndex(to);

  if (fIndex == -1 || tIndex == -1) {
    cout << "vertices not found" << endl;
    return;
  }

  edge* current = nodes[fIndex]->head;
  while (current != nullptr) {
    if (current->toIndex == tIndex) {
      current->weight = weight;
      return;
    }
    
    current = current->next;
  }

  edge* newEdge = new edge;
  newEdge->toIndex = tIndex;
  newEdge->weight = weight;
  newEdge->next = nodes[fIndex]->head;
  
  nodes[fIndex]->head = newEdge;
}

void graph::removeEdge(const char* from, const char* to) {
  int fIndex = getIndex(from);
  int tIndex = getIndex(to);

  if (fIndex == -1 || tIndex == -1) {
    cout << "vertices not found" << endl;
    return;
  }

  edge* current = nodes[fIndex]->head;
  edge* prevEdge = nullptr;

  while (current != nullptr) {
    if (current->toIndex == tIndex) {
      if (prevEdge == nullptr) {
        nodes[fIndex]->head = current->next;
      } else {
        prevEdge->next = current->next;
      }
      
      delete current;
      return;
    }
    
    prevEdge = current;
    current = current->next;
  }
  cout << "no edge found" << endl;
}

void graph::printAdjacencyList() {
  for (int i = 0; i < nodes.size(); i++) {
    
    cout << nodes[i]->label << ": ";
    edge* current = nodes[i]->head;
    
    while (current != nullptr) {
      cout << "(" << nodes[current->toIndex]->label << ", " << current->weight << ") ";
      current = current->next;
    }
    
    cout << endl;
  }
}

void graph::shortestPath(const char* from, const char* to) {
  int start = getIndex(from);
  int end = getIndex(to);

  if (start == -1 || end == -1) {
    cout << "vertices not found" << endl;
    return;
  }

  const int verylargenumber = 9999999;
  
  int size = nodes.size();
  int* dist = new int[size];
  int* prev = new int[size];
  bool* visited = new bool[size];

  for (int i = 0; i < size; ++i) {
    dist[i] = verylargenumber;
    prev[i] = -1;
    visited[i] = false;
  }

  dist[start] = 0;

  for (int count = 0; count < size; ++count) {
    int minDist = verylargenumber;
    int u = -1;

    for (int i = 0; i < size; ++i) {
      if (!visited[i] && dist[i] < minDist) {
        minDist = dist[i];
        u = i;
      }
    }

    if (u == -1) {
      break;
    }

    visited[u] = true;
    edge* current = nodes[u]->head;
      
    while (current != nullptr) {
      int v = current->toIndex;
      int w = current->weight;
        
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        prev[v] = u;
      }
        
      current = current->next;
    }
  }

  if (dist[end] == verylargenumber) {
    cout << "there is no path" << endl;
  } else {
    cout << "shortest path takes: " << dist[end] << endl;
    cout << "path: ";

    int path[100];
    int len = 0;
      
    for (int v = end; v != -1; v = prev[v]) {
      path[len++] = v;
    }

    for (int i = len - 1; i >= 0; --i) {
      cout << nodes[path[i]]->label;
        
      if (i > 0) {
        cout << "->";
      }
        
    }
    cout << endl;
  }

  delete[] dist;
  delete[] prev;
  delete[] visited;
}





