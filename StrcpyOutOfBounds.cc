#include <iostream>
#include <string.h>

char StrncpyOutOfBounds() {
    char *x = (char *)malloc(64);
    char *y = (char *)malloc(72);
    strncpy(x, y, 72);
    return x[55];
}

int main(int argc, char **argv) {
  std::cout << StrncpyOutOfBounds() << std::endl;
  return 0;
}
