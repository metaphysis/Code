// WhatFix Notation
// UVa ID: 372
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

string getPostfix(string prefix, string infix)
{
    return "";
}

int main(int argc, char *argv[])
{
    string infix, prefix, postfix;
    while (getline(cin, infix), getline(cin, prefix))
    {
        cout << "INFIX   => " << infix << '\n';
        cout << "PREFIX  => " << prefix << '\n';
        cout << "POSTFIX => " << getPostfix(infix, prefix) << '\n';
    }

    return 0;
}
