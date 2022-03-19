#!/bin/sh
g++ -std=c++11 1-1-3.cpp
a.out >second.cpp
g++ -std=c++11 second.cpp
a.out >third.txt
cat third.txt
