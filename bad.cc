#include <iostream>
#include <cstdint>

#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

static jmp_buf my_jmp_buf;

static char global_buffer_k[64];

int32_t Negate(int32_t x) {
    return -x;
}

int32_t Shift(int32_t x, size_t shift) {
    return x << shift;
}

bool IsEven(int32_t *x) {
    return (*x % 2) == 0;
}

char BufferFetch(char *buffer, size_t index) {
    return buffer[index];
}

char HeapOutOfBounds() {
    char *buffer = (char*) malloc(128);
    char ret = buffer[130];
    free(buffer);
    return ret;
}

char GlobalOutOfBounds(size_t pos) {
    return global_buffer_k[pos];
}

int32_t SignedAddition(int32_t x, int32_t y) {
    return x + y;
}

int32_t GetMaxInt32() {
    uint32_t t = 1UL << 31;
    return static_cast<int32_t>(t - 1);
}

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

char MemcpyOutOfBounds() {
    char *x = (char *)malloc(64);
    char *y = (char *)malloc(72);
    memcpy(x, y, 72);
    return x[55];
}

char StrncpyOutOfBounds() {
    char *x = (char *)malloc(64);
    char *y = (char *)malloc(128);
    strncpy(x, y, 128);
    return x[55];
}

size_t StrncpyNotNullTerminated() {
    char x[16];
    strncpy(x, "This is a string that is longer than 16 bytes I am sorry to say", sizeof(x));
    return strlen(x);
}

int32_t IntegerTruncation(int64_t x) {
    // This is caught with gcc -Wconversion
    return x;
}

int64_t DoubleTruncation(double x) {
    // This is caught with gcc -Wfloat-conversion
    return x;
}  

#ifdef ENABLE_WERROR_TESTS
int32_t *ReturnStackPointer() {
    int32_t x[256] = {0};
    return &x[37];
}
#endif

void UseAfterReturn(int32_t **out) {
    int32_t x[256] = {0};
    *out = &x[37];
}

char *MemoryLeak() {
    char *x = (char *)malloc(128);
    return x;
}

int32_t Divide(int32_t x, int32_t y) {
    return x / y;
}

void SignalHandler(int signum) {
    // Do stuff here then return to execution below
    longjmp(my_jmp_buf, 1);
}

int64_t VlaTest(ssize_t sz) {
    int64_t vla[sz];
    for (ssize_t i=0; i < sz; ++i) {
        vla[i] = i;
    }
    return vla[sz - 1];
}

int32_t *MallocAndFree() {
    int32_t *x = (int32_t *)malloc(sizeof(int32_t));
    free(x);
    return x;
}

int main(int argc, char **argv) {
    char buffer[256];
    int32_t uninit;

    signal(SIGFPE, SignalHandler);
    
    // static array index out-of-bounds:
    // gcc finds this via -Warray-bounds
#ifdef ENABLE_WERROR_TESTS
    std::cout << "STATIC OUT-OF-BOUNDS: " << buffer[312] << std::endl;
#endif

    std::cout << "DYNAMIC STACK OUT-OF-BOUNDS: " << BufferFetch(buffer, 312) << std::endl;

    std::cout << "HEAP OUT-OF-BOUNDS: " << HeapOutOfBounds() << std::endl;

    std::cout << "GLOBAL OUT-OF-BOUNDS: " << GlobalOutOfBounds(72) << std::endl;
    
    {
        int32_t x = 2147483647;
        int32_t y = 107;
        std::cout << "STATIC SIGNED OVERFLOW: " << x + y << std::endl;
    }

    {
        int32_t x = GetMaxInt32();
        int32_t y = 71;
        
        std::cout << "DYNAMIC SIGNED OVERFLOW: " << x << " " << x + y << std::endl;
    }

#ifdef ENABLE_WERROR_TESTS
    std::cout << "READ UNITIALIZED: " << uninit << std::endl;
#endif

    {
        int x;
        std::cout << "READ UNITIALIZED INDIRECT " << IsEven(&x) << std::endl;
    }
    
    std::cout << "SWITCH FALL THROUGH " << SwitchFallThrough(3) << std::endl;

    std::cout << "MEMCPY OUT OF BOUNDS " << MemcpyOutOfBounds() << std::endl;

    std::cout << "STRNCPY OUT OF BOUNDS " << StrncpyOutOfBounds() << std::endl;

    std::cout << "STRNCPY NOT NULL TERMINATED " << StrncpyNotNullTerminated() << std::endl;

    {
        int32_t *x;
        UseAfterReturn(&x);
        std::cout << "USE AFTER RETURN " << x << std::endl;
    }

    {
        int64_t x = 1LL << 31;
        std::cout << "INTEGER TRUNCATION: " << IntegerTruncation(x) << std::endl;
    }

    {
        double x = std::numeric_limits<double>::max();
        std::cout << "DOUBLE TRUNCATION: " << DoubleTruncation(x) << std::endl;
    }

    {
        char *x = MemoryLeak();
        std::cout << "MEMORY LEAK: " << x[0] << std::endl;
    }

    {
        int32_t x = 102;
        int32_t y = 0;
        if (setjmp(my_jmp_buf) == 0) {
            std::cout << "DIVIDE BY ZERO: " << Divide(x, y) << std::endl;
        } else {
            std::cout << std::endl;
        }
    }

    std::cout << "BIG ASS VARIABLE LENGTH ARRAY " << VlaTest(65536) << std::endl;

    std::cout << "NEGATIVE VARIABLE LENGTH ARRAY " << VlaTest(-8) << std::endl;

    {
        // Negating int_min has undefined behavior
        // https://blog.regehr.org/archives/226
        int32_t x = std::numeric_limits<int32_t>::min();
        std::cout << "NEGATE INT_MIN " << Negate(x) << std::endl;
    }

    {
        int32_t x = 1089;        
        std::cout << "SHIFT PAST BIT WIDTH " << Shift(x, 35) << std::endl;
    }

    {
        int32_t *x = MallocAndFree();
        std::cout << "USE AFTER FREE " << *x << std::endl;
    }

#ifdef ENABLE_DOUBLEFREE_TEST
    // Generates a runtime error on MacOS 10.14.6
    {
        int32_t *x = MallocAndFree();
        free(x);
        std::cout << "DOUBLE FREE " << *x << std::endl;
    }
#endif

   
    return 0;
}
