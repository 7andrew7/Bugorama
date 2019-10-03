#include <iostream>
#include <cstdint>

int main(int argc, char **arg) {
  int32_t x = 2147483647;
  int32_t y = 107;
  std::cout << "STATIC SIGNED OVERFLOW: " << x + y << std::endl;
  return 0;
}
