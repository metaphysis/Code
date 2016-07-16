// Counting Patterns
// UVa ID: 269
// Verdict: Accepted
// Submission Date: 2016-06-04
// UVa Run Time: 0.240s
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

int n, k, digits[16], permutation[32], configuration[100000][16], solutions;

bool isLarger(int p[])
{
    int i;
    for (i = 0; p[i] == digits[i] && i < n; i++)
        ;
    return i < n && p[i] > digits[i];
}

// make sure it is the lexicographically largest
bool isLexicographicallyLargest()
{
    for (int i = 0; i < n; i++)
        permutation[i] = digits[i], permutation[i + n] = digits[i];

    for (int i = 1; i < n; i++)
        if (permutation[i] == digits[0] && isLarger(permutation + i))
            return false;

    for (int i = 0; i < 2 * n; i++)
        permutation[i] = -permutation[i];

    for (int i = 1; i < n; i++)
        if (permutation[i] == digits[0] && isLarger(permutation + i))
            return false;

    for (int i = n - 1; i >= 0; i--)
        permutation[n - i - 1] = digits[i], permutation[2 * n - i - 1] = digits[i];

    for (int i = 0; i < n; i++)
        if (permutation[i] == digits[0] && isLarger(permutation + i))
            return false;

    for (int i = 0; i < 2 * n; i++)
        permutation[i] = -permutation[i];

    for (int i = 0; i < n; i++)
        if (permutation[i] == digits[0] && isLarger(permutation + i))
            return false;

    return true;
}

void dfs(int depth, int sumCurrent)
{
    if (depth == n)
    {
        if (sumCurrent == 0 && isLexicographicallyLargest())
        {
            for (int i = 0; i < n; i++)
                configuration[solutions][i] = digits[i];
            solutions++;
        }
    }
    // pruning
    else if (abs(sumCurrent) <= (n - depth) * digits[0])
    {
        // search
        for (int d = -digits[0]; d <= digits[0]; d++)
        {
            digits[depth] = d;

            // pruning: is the sequence can be larger?
            if (digits[depth - 1] == digits[0] && digits[depth] > digits[1])
                break;

            // pruning: is the reversed sequence can be larger?
            if (digits[depth] == digits[0] && digits[depth - 1] > digits[1])
                break;

            // continue search
            sumCurrent += d;
            dfs(depth + 1, sumCurrent);
            sumCurrent -= d;
        }
    }
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> n >> k)
    {
        if (cases++)
            cout << endl;

        solutions = 0;
        for (int start = 0; start <= k; start++)
        {
            digits[0] = start;
            dfs(1, start);
        }

        cout << solutions << endl;
        for (int i = 0; i < solutions; i++)
        {
            for (int j = 0; j < n; j++)
                cout << (j ? ',' : '(') << configuration[i][j];
            cout << ')' << endl;
        }
    }

    return 0;
}
