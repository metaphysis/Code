// My Password is a Palindromic Prime Number
// UVa ID: 13209
// Verdict: Accepted
// Submission Date: 2017-11-18
// UVa Run Time: 0.160s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXN = 100100;

int main(int argc, char *argv[])
{
    int cases, numerator, denominator;
    int digits[MAXN], position[MAXN], appeared[MAXN], idx;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> denominator;

        idx = 0, numerator = 1;
        memset(appeared, 0, sizeof(appeared));

        while (!appeared[numerator] && numerator > 0)
        {
            appeared[numerator] = 1;
            digits[idx] = 10 * numerator / denominator;
            position[numerator] = idx++;
            numerator = 10 * numerator % denominator;
        }

        cout << "0.";
        for (int i = 0; i < idx; i++) cout << digits[i];
        cout << '\n';
    }

    return 0;
}
