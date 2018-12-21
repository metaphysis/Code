#!/bin/sh
g++ -std=c++11 in.cpp
a.out >in.txt
g++ -std=c++11 program.cpp
a.out <in.txt >out.txt
g++ -std=c++11 program1.cpp
a.out <in.txt >out1.txt
diff out.txt out1.txt
