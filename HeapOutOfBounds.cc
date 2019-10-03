#include <iostream>

char HeapOutOfBounds() {
    char *buffer = (char*) malloc(128);
    char ret = buffer[130];
    free(buffer);
    return ret;
}

int main(int argc, char **argv) {
  std::cout << HeapOutOfBounds() << std::endl;
  return 0;
}
