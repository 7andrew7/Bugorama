#include <iostream>
#include <cstdint>

void UseAfterReturn(int32_t **out) {
    int32_t x[256] = {0};
    *out = &x[37];
}

int main(int argc, char **argv) {
  int32_t *x;
  UseAfterReturn(&x);
  std::cout << "USE AFTER RETURN " << x << std::endl;
}
