#include <iostream>
#include <cstdint>

#include <string.h>

void MemcpyWrapper(void *dst, const void *src, size_t n) {
    memcpy(dst, src, n);
}

bool IsEven(int32_t *x) {
  return (*x % 2) == 0;
}

char StrncpyWrapper(char *x, char *y, size_t sz) {
    strncpy(x, y, sz);
    return x[55];
}
