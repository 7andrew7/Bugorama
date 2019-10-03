#include <iostream>

bool IsEven(int *x) {
    return (*x % 2) == 0;
}

int main(int argc, char **argv) {
  int x;
  std::cout << IsEven(&x) << std::endl;
  return 0;
}
