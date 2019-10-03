#include <iostream>
#include <string.h>

char StrncpyOutOfBounds(char *x, char *y, size_t sz) {
    strncpy(x, y, sz);
    return x[55];
}

int main(int argc, char **argv) {
  char *x = (char *)malloc(64);
  char *y = (char *)malloc(72);

  std::cout << StrncpyOutOfBounds(x, y, 72) << std::endl;
  return 0;
}
