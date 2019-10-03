#include <iostream>
#include <cstdint>

#include <stdlib.h>
#include <string.h>

int32_t *MallocAndFree() {
  int32_t *x = (int32_t *)malloc(4);
  *x = 7;
  free(x);
  return x;
}

int main()  {
  int32_t *x = MallocAndFree();
  std::cout << "USE AFTER FREE " << *x << std::endl;
  return 0;
}
