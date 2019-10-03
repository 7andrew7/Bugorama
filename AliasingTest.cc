#include <iostream>
#include <cstdint>

// https://blog.regehr.org/archives/959
int AliasingTest(int *h, long *k) {
    *h = 5;
    *k = 6;
    return *h;
}

int main() {
  long k;
  int x = AliasingTest((int *)&k, &k);
  std::cout << "ALIASING  " << x << std::endl;
}
