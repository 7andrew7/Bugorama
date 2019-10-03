#include <iostream>
#include <string.h>

size_t StrncpyNotNullTerminated() {
    char x[16];
    strncpy(x, "This is a string that is longer than 16 bytes I am sorry to say", sizeof(x));
    return strlen(x);
}

int main(int argc, char **argv) {
  std::cout << "STRNCPY NOT NULL TERMINATED " << StrncpyNotNullTerminated() << std::endl;
  return 0;
}
