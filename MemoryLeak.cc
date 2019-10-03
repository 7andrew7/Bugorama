#include <iostream>
#include <cstdint>
#include <string.h>

char *MemoryLeak() {
  return (char *)malloc(128);
}

int main() {
  char *x = MemoryLeak();
  std::cout << "MEMORY LEAK: " << x[0] << std::endl;
  return 0;
}
