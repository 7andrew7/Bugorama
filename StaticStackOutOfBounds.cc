#include <iostream>

// Directly reference out-of-bounds stack memory.
int main(int argc, char **argv) {
    char buffer[256];
    std::cout << "STACK OUT-OF-BOUNDS: " << buffer[260] << std::endl;
    return 0;
}
