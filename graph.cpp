#include "graph.h"
#include <iostream>
#include <cstring>

node::node(const char* name) {
  strncpy(label, name, 19);
  label[19] = '\0';
  head = nullptr;
}
