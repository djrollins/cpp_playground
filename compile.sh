#!/bin/bash
clang++ -o $1 -std=c++14 -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic "./$1.cpp" && ./$1
