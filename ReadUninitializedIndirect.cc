#include <iostream>

bool IsEven(int *x);

int main(int argc, char **argv) {
  int x;
  std::cout << IsEven(&x) << std::endl;
  return 0;
}
