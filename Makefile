
SRCS := $(wildcard *.cc)
EXCLUDED := main.cc test.cc
FILTERED := $(filter-out $(EXCLUDED),$(SRCS))

EXES := $(FILTERED:%=%.exe)
CXXFLAGS := -std=c++17 -O0 -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable

all: $(EXES)

%.cc.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@


.PHONY: clean

clean:
	$(RM) -r *.cc.exe

