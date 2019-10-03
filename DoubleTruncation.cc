#include <iostream>
#include <cstdint>

int64_t DoubleTruncation(double x) {
    // This is caught with gcc -Wfloat-conversion
    return x;
}  

int main() {
  double x = std::numeric_limits<double>::max();
  std::cout << "DOUBLE TRUNCATION: " << DoubleTruncation(x) << std::endl;
}
