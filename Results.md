# Bug-o-Rama Results

This documents summarizes results from October 2019 running with various compilers and analysis tools.

## Software Tested

- GCC7=gcc version 7.4.0
- CL8=clang 8.0.0-3
- CL8+SA=clang8 + [static analyzer]([https://clang-analyzer.llvm.org](https://clang-analyzer.llvm.org/))
- CL8+AU=clang8 + [address sanitizer](https://clang.llvm.org/docs/AddressSanitizer.html) + [undefined behavior sanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html).  Note that address sanitizer now implies the leak sanitizer.
- CL8+MS=clang8 + [memory sanitizer](https://clang.llvm.org/docs/MemorySanitizer.html) (incompatible with address sanitizer)
- CPPC=[CppCheck](http://cppcheck.sourceforge.net/) 1.82
- VG=[valgrind](http://valgrind.org/) 3.13.0

All tests were run on Ubuntu 18.04 on an t2.xlarge instance.

## Configuration

The compiler flags were as follows:

```
CSSFLAGS := -std=c++17 -O2 -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable
```

This does not leverage all possible warnings.  In particular, `-Wconversion` (and friends) would likely detect the trunction errors (IntegerTruncation, DoubleTruncation).

Clang8 Address Sanitizer + Undefined Sanitizer flags:

```
CXXFLAGS := -std=c++17 -O1 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable
```

These runs used: `ASAN_OPTIONS="detect_stack_use_after_return=1"`

Valgrind used gcc7's output with these command line options:

```
valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes
```

## Results

<span style="color:red">FAIL</span> indicates that no error was generated.

<span style="color:darkgreen">PASS</span> indicates that the tool caught the error, either at compile time or runtime.

<span style="color:darkgreen">PASS</span>* indicates that the test was filtered out by a previous stage (e.g., gcc rejects the test before valgrind can execute it).

| Test                             | GCC7 | CL8 | CL8+SA | CL8+AU | CL8+MS | CPPC | VG |
| -------------------------------- | ---- | ------ | --------- | -------- | -------- | -------- | -------- |
|AliasingTest.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|
|BigAssVla.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|
|DoubleFree.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|
|DoubleTruncation.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|
|GlobalOutOfBounds.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|
|HeapOutOfBounds.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|
|IntegerTruncation.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|
|MemcpyOutOfBounds.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|
|MemoryLeak.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|
|NegativeVla.cc| <span style="color:darkgreen">PASS</span> |<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>*|
|ReadUninitialized.cc| <span style="color:darkgreen">PASS</span> |<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>*|
|ReadUninitializedIndirect.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|
|ShiftPastBitWidth.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|
|SignedOverflow.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|
|StackOutBounds.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|
|StaticStackOutOfBounds.cc| <span style="color:darkgreen">PASS</span> | <span style="color:darkgreen">PASS</span> |<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>*|
|StrcpyOutOfBounds.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|
|StrncpyNotNullTerminated.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|
|SwitchFallThrough.cc| <span style="color:darkgreen">PASS</span> |<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>*|
|UseAfterFree.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|
|UseAfterRet.cc|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|<span style="color:darkgreen">PASS</span>|<span style="color:red">FAIL</span>|<span style="color:darkgreen">PASS</span>|

## Notes

The ASAN/Valgrind comparison [described here](https://github.com/google/sanitizers/wiki/AddressSanitizerComparisonOfMemoryTools) is mostly accurate.  Valgrind is the only system that reliably detects most accesses to uninitialized data.  However, valgrind struggles to detect out-of-bounds accesses to global data and stack data, presumably because the tool doesn't understand the semnatics of these accesses.  The clang UB sanitizer is the only tool that detects "undefined" behaviors such as signed integer overflow and shift-past-bit-width  In contrast to the google wiki, I found that Valgrind was able to detect use-after-return errors.  I didn't find the clang memory sanitizer to be much use.

As a general comment, gcc7 is very bad about reporting different failure modes for different optimization levels.  -O2 seems to generate more warnings/errors than -O0.

cpp-check was surprisingly useful.  However, I suspect that the static analysis tools can be fooled by moving code around within compilation units: e.g., ReadUnitialized versus ReadUninitializedIndirect.
