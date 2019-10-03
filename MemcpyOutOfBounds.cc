#include <iostream>
#include <string.h>

char MemcpyWrapper(void *dst, const void *src, size_t n);

int main(int argc, char **argv) {
  char buf1[128];
  char buf2[256];

  MemcpyWrapper(buf1, buf2, sizeof(buf2));
  return 0;
}
