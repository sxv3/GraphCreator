#include "graph.h"
#include <iostream>

//main.cpp file to run program
//by Tai Wong, 5/29/2025

using namespace std;

int main() {
  graph g;
  int choice;
  char label1[20], label2[20];
  int weight;

  cout << "1->add vertex" << endl;
  cout << "2->add edge" << endl;
  cout << "3->remove vertex" << endl;
  cout << "4->remove edge" << endl;
  cout << "5->find shortest path" << endl;
  cout << "6->print" << endl;
  cout << "7->exit" << endl;

  while (true) {
    cout << "enter choice: " << endl;
    cin >> choice;

    if (choice == 1) {
      cout << "enter vertex label: ";
      cin >> label1;
      g.addVertex(label1);
    } else if (choice == 2) {
      cout << "enter from vertex: ";
      cin >> label1;
      cout << "enter to vertex: ";
      cin >> label2;
      cout << "enter edge weight: ";
      cin >> weight;
      g.addEdge(label1, label2, weight);
    } else if (choice == 3) {
      cout << "enter vertex to remove: ";
      cin >> label1;
      g.removeVertex(label1);
    } else if (choice == 4) {
      cout << "enter from vertex: ";
      cin >> label1;
      cout << "enter to vertex: ";
      cin >> label2;
      g.removeEdge(label1, label2);
    } else if (choice == 5) {
      cout << "enter start vertex: ";
      cin >> label1;
      cout << "enter end vertex: ";
      cin >> label2;
      g.shortestPath(label1, label2);
    } else if (choice == 6) {
      g.printAdjacencyList();
    } else if (choice == 7) {
      break;
    } else {
      cout << "bad input" << endl;
    }
  }
}
