#include <iostream>
#include <cstdint>

int32_t Shift(int32_t x, size_t shift) {
    return x << shift;
}

int main() {
  int32_t x = 1089;        
  std::cout << "SHIFT PAST BIT WIDTH " << Shift(x, 35) << std::endl;
}
