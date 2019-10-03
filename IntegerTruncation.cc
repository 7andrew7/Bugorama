#include <iostream>
#include <cstdint>

int32_t IntegerTruncation(int64_t x) {
    // This is caught with gcc -Wconversion
    return x;
}

int main(int argc, char **argv) {
  int64_t x = 1LL<<32;
  std::cout << "INTEGER TRUNCATION " << IntegerTruncation(x) << std::endl;
}
