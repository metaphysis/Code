// Ouroboros Snake
// UVa ID: 10040
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

const int MAXV = 1024 * 1024 * 2;

int used[MAXV], sequence[MAXV];
int n, k, bits, solved;

void dfs(int i, int counter)
{
    if (solved) return;

    if (counter == bits)
    {
        cout << sequence[k] << '\n';
        solved = true;
        return;
    }

    int next = (i & ((1 << (n - 1)) - 1)) << 1;

    if (!used[next])
    {
        used[next] = 1, sequence[counter] = next;
        dfs(next, counter + 1);
        if (solved) return;
        used[next] = 0;
    }

    if (!used[next + 1])
    {
        used[next + 1] = 1, sequence[counter] = next + 1;
        dfs(next + 1, counter + 1);
        if (solved) return;
        used[next + 1] = 0;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> k;
        
        memset(used, 0, sizeof(used));
        memset(sequence, 0, sizeof(sequence));
        solved = false;
        bits = pow(2, n);

        dfs(0, 0);
    }
    
    return 0;
}
