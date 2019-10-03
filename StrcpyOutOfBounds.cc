#include <iostream>
#include <string.h>

char StrncpyWrapper(char *x, char *y, size_t sz);

int main(int argc, char **argv) {
  char *x = (char *)malloc(64);
  char *y = (char *)malloc(72);

  std::cout << StrncpyWrapper(x, y, 72) << std::endl;
  return 0;
}
