#include <iostream>

// Reference out-of-bounds stack memory via a helper function

char BufferFetch(char *buffer, size_t index) {
    return buffer[index];
}

int main(int argc, char **argv) {
  char buffer[256] = {0};
  char c = BufferFetch(buffer, 259);
  std::cout << c << std::endl;
}

  
