// WhatFix Notation
// UVa ID: 372
// Verdict: Accepted
// Submission Date: 2017-02-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

vector<char> sequences;

void postfix(string prefix, string infix)
{
    if (prefix.length() == 0) return;
    
    // 找到根结点。
    int root = 0;
    for (; root < infix.length(); root++)
        if (infix[root] == prefix.front())
            break;

    // 在左子树中递归。
    postfix(prefix.substr(1, root), infix.substr(0, root));

    // 在右子树中递归。
    postfix(prefix.substr(root + 1), infix.substr(root + 1));

    // 输出根。
    sequences.push_back(prefix.front());
}

int main(int argc, char *argv[])
{
    string infix, prefix;
    while (getline(cin, infix), getline(cin, prefix))
    {
        cout << "INFIX   => " << infix << '\n';
        cout << "PREFIX  => " << prefix << '\n';
        
        for (int i = infix.size() - 1; i >= 0; i--)
            if (isblank(infix[i]))
                infix.erase(infix.begin() + i);
        for (int i = prefix.size() - 1; i >= 0; i--)
            if (isblank(prefix[i]))
                prefix.erase(prefix.begin() + i);
        
        sequences.clear();
        postfix(prefix, infix);
        
        cout << "POSTFIX =>";
        for (int i = 0; i < sequences.size(); i++)
            cout << ' ' << sequences[i];
        cout << '\n';
    }

    return 0;
}
