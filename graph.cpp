#include "graph.h"
#include <iostream>
#include <cstring>

using namespace std;


//graph.cpp implementation file for graph class
//by Tai Wong May 29th

//node constructor
node::node(const char* name) {
  strncpy(label, name, 19);
  label[19] = '\0';
  head = nullptr;
}

//node destructor, delets any edges connected to it
node::~node() {
  edge* current = head;
  
  while (current != nullptr) {
    
    edge* nextEdge = current->next;
    current = nullptr;
    
    delete current;
    current = nextEdge;
  }
}

//graph destructor, clears vector
graph::~graph() {
  for (int i = 0; i < nodes.size(); i++) {
    nodes[i] = nullptr;    
    delete nodes[i];
  }
  
  nodes.clear();
}

//get index of a node based on name
int graph::getIndex(const char* name) {
  for (int i = 0; i < nodes.size(); i++) {
    if (strcmp(nodes[i]->label, name) == 0) {
      return i;
    }
  }
  
  return -1;
}

//add vertex to graph
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

//remove vertex func
void graph::removeVertex(const char* name) {
  int index = getIndex(name);
  
  if (index == -1) {
    cout << "vertex not found" << endl;
    return;
  }

  //remove any incoming edges
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

  // shift indicies
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

//add edge function
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

  //add edge at list front
  edge* newEdge = new edge;
  newEdge->toIndex = tIndex;
  newEdge->weight = weight;
  newEdge->next = nodes[fIndex]->head;
  
  nodes[fIndex]->head = newEdge;
}

//remove edge function
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

//print adjacency list
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

//shortest path via dijikstras algorithm
void graph::shortestPath(const char* from, const char* to) {
  int start = getIndex(from);
  int end = getIndex(to);

  if (start == -1 || end == -1) {
    cout << "vertices not found" << endl;
    return;
  }

  const int verylargenumber = 9999999;
  
  int size = nodes.size();
  int* dist = new int[size]; //holds shortest distance to each vertex
  int* prev = new int[size]; //used to reconstruct path
  bool* visited = new bool[size]; //track visited vertices

  for (int i = 0; i < size; ++i) {
    dist[i] = verylargenumber;
    prev[i] = -1;
    visited[i] = false;
  }

  dist[start] = 0;

  //main loop for dijikistras
  for (int count = 0; count < size; ++count) {
    int minDist = verylargenumber;
    int u = -1;

    //select unvisited node with shortest distance
    for (int i = 0; i < size; ++i) {
      if (!visited[i] && dist[i] < minDist) {
        minDist = dist[i];
        u = i;
      }
    }

    if (u == -1) {
      break; //reached all nodes
    }

    visited[u] = true;
    edge* current = nodes[u]->head;

    //relax edges from u
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

  //print results
  if (dist[end] == verylargenumber) {
    cout << "there is no path" << endl;
  } else {
    cout << "shortest path takes: " << dist[end] << endl;
    cout << "path: ";

    int path[100];
    int len = 0;

    //reconstruct path
    for (int v = end; v != -1; v = prev[v]) {
      path[len++] = v;
    }

    //print in correct order
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





