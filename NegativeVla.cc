#include <iostream>
#include <cstdint>

int64_t VlaTest(ssize_t sz) {
    int64_t vla[sz];
    for (ssize_t i=0; i < sz; ++i) {
        vla[i] = i;
    }
    return vla[sz - 1];
}

int main(int argc, char **argv) {
  std::cout << "NEGATIVE VLA " << VlaTest(-8) << std::endl;
  return 0;
}
