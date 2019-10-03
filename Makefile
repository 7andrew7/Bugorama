
SRCS := $(wildcard *.cc)

# ReadUninitialized.cc is rejected via -Werror=uninitialized on gcc 7.4.0
# SwitchFallThrough rejected by gcc implicit-fallthrough on gcc 7+
# StaticStackOutOfBounds.cc is rejected by gcc 7 at -O2 (but not at -o0 sadly)
# StrcpyOutOfBounds.cc is rejected at by gcc 7 at -O2 (but not -O0)
# MemcpyOutOfBounds.cc is similar
# NegativeVla is similar
EXCLUDED := main.cc ReadUninitialized.cc SwitchFallThrough.cc StaticStackOutOfBounds.cc StrcpyOutOfBounds.cc MemcpyOutOfBounds.cc NegativeVla.cc 
FILTERED := $(filter-out $(EXCLUDED),$(SRCS))

EXES := $(FILTERED:%=%.exe)
CXXFLAGS := -std=c++17 -O2 -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable

all: $(EXES)

%.cc.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@


.PHONY: clean

clean:
	$(RM) -r *.cc.exe

