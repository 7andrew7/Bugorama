#include <iostream>
#include <cstdint>

int32_t SwitchFallThrough(int32_t arg) {
    int32_t x = 0;
    switch(arg) {
        case 7:
            x++;
        case 8:
            x++;
    }
    return x;
}

int main(int argc, char **argv) {
  std::cout << SwitchFallThrough(7) << std::endl;
  return 0;
}
