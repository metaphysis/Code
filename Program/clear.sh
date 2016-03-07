#!/bin/sh
find . -name *.cpp~ -exec rm -fv {} \;
find . -name *.out -exec rm -fv {} \;
find . -name *.txt~ -exec rm -fv {} \;
