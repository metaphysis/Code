#!/bin/sh
#g++ -std=c++11 in.cpp -o a1.out
a1.out >in.txt
#g++ -std=c++11 program.cpp -o a2.out
a2.out <in.txt >out.txt
#g++ -std=c++11 program1.cpp -o a3.out
a3.out <in.txt >out1.txt
diff out.txt out1.txt >diff.txt
cat diff.txt
