#include <iostream>
#include <string.h>

char MemcpyOutOfBounds() {
    char *x = (char *)malloc(64);
    char *y = (char *)malloc(72);
    memcpy(x, y, 72);
    return x[55];
}

int main(int argc, char **argv) {
  std::cout << MemcpyOutOfBounds() << std::endl;
  return 0;
}
