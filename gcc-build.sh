#!/bin/sh

set -x
g++ -std=c++17 -O0 -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable bad.cc
