#include <iostream>

static char buffer[128];

char GlobalOutOfBounds(size_t i) {
  return buffer[i];
}

int main(int argc, char **argv) {
  std::cout << GlobalOutOfBounds(130) << std::endl;
  return 0;
}
