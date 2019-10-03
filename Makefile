
SRCS := $(wildcard *.cc)

# ReadUninitialized.cc is rejected via -Werror=uninitialized on gcc 7.4.0
# SwitchFallThrough rejected by gcc implicit-fallthrough on gcc 7+
EXCLUDED := main.cc ReadUninitialized.cc SwitchFallThrough.cc
FILTERED := $(filter-out $(EXCLUDED),$(SRCS))

EXES := $(FILTERED:%=%.exe)
CXXFLAGS := -std=c++17 -O0 -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable

all: $(EXES)

%.cc.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@


.PHONY: clean

clean:
	$(RM) -r *.cc.exe

