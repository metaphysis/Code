#!/bin/sh
g++ -std=c++11 11.5.2.1.in.cpp
a.out >11.5.2.1.in
g++ -std=c++11 11.5.2.1.cpp
a.out <11.5.2.1.in >11.5.2.1.out
g++ -std=c++11 11.9.6.cpp
a.out <11.5.2.1.in >11.9.6.out1
diff 11.5.2.1.out 11.9.6.out1
