#!/bin/bash

#grep '^#include <iostream>' -rl ./ >list.txt

cat list.txt | while read line
do
    sed -i "/^#include/d" "$line";
    sed -i "N;/\nusing namespace std;/!P;D" "$line";
    sed -i "/^using namespace std;/i \#include <bits/stdc++.h>\n" "$line";
done

