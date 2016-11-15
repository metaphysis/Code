#!/bin/sh
g++ -std=c++11 in.cpp
a.out >in.txt
g++ -std=c++11 program.cpp
a.out <in.txt >out.txt
g++ -std=c++11 answer.cpp
a.out <in.txt >answer.txt
diff out.txt answer.txt >diff.txt
cat diff.txt
