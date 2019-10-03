
# Override to use a specific compiler
#CXX := /usr/bin/clang++-8

SRCS := $(wildcard *.cc)

# ReadUninitialized.cc is rejected via -Werror=uninitialized on gcc 7.4.0
# SwitchFallThrough rejected by gcc implicit-fallthrough on gcc 7+
# StaticStackOutOfBounds.cc is rejected by gcc 7 at -O2 (but not at -o0 sadly)
# NegativeVla is similar
GCC7_EXCLUDED := ReadUninitialized.cc SwitchFallThrough.cc StaticStackOutOfBounds.cc NegativeVla.cc

# Clang8 out-of-the box catches less than gcc7
CLANG8_EXCLUDED := StaticStackOutOfBounds.cc

# clang8 static analyzer: /usr/bin/scan-build-8 make
# Note that other tests generate warnings: HeapOutOfBounds.cc, DoubleFree.cc, NegativeVla.cc
CLANG8_SA_EXCLUDED := StaticStackOutOfBounds.cc ReadUninitialized.cc SwitchFallThrough.cc

EXCLUDED := $(GCC7_EXCLUDED)

FILTERED := $(filter-out $(EXCLUDED) helpers.cc,$(SRCS))

EXES := $(FILTERED:%=%.exe)
CXXFLAGS := -std=c++17 -O2 -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable

all: $(EXES)

%.cc.exe: %.cc helpers.o
	$(CXX) $(CXXFLAGS) $< helpers.o -o $@

helpers.o: helpers.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r *.o
	$(RM) -r *.cc.exe

