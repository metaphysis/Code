// Happy Numbers
// UVa ID: 944
// Verdict: Accepted
// Submission Date: 2017-03-08
// UVa Run Time: 0.050s
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

const int MAXN = 100000;

int iterations[MAXN], happy[MAXN];

void check(int n)
{
    int original, next = n, remainder;
    unordered_set<int> appeared;
    
    int elapsed = 0;
    while (true)
    {
        if (happy[next] == 1)
        {
            happy[n] = 1;
            iterations[n] = iterations[next] + elapsed;
            break;
        }
        else if (happy[next] == -1 || appeared.find(next) != appeared.end())
        {
            for (auto v : appeared) happy[v] = -1;
            break;
        }

        appeared.insert(next);
        original = next, next = 0;

        while (original > 0)
        {
            remainder = original % 10;
            next += remainder * remainder;
            original /= 10;
        }

        elapsed++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    memset(happy, 0, sizeof(happy));
    happy[1] = 1, iterations[1] = 1;
    
    for (int i = 2; i < MAXN; i++)
    {
        if (happy[i] == -1) continue;
        check(i);
    }
    
    int counter = 0;
    for (int i = 1; i < MAXN; i++)
        if (happy[i] == 1) happy[counter++] = i;

    int cases = 0, L, H;
    
    while (cin >> L >> H)
    {
        if (L > H) swap(L, H);
        if (cases++ > 0) cout << '\n';
        for (int i = 0; i < counter; i++)
            if (happy[i] >= L && happy[i] <= H)
                cout << happy[i] << ' ' << iterations[happy[i]] << '\n';
    }
    
    return 0;
}
