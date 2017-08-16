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

int n, k;
int used[1 << 21], sequence[1 << 21], top;
int bits, mask;

void dfs(int u)
{
    u = (u & mask) << 1;
    for (int v = 0; v <= 1; v++)
    {
        if (used[u + v]) continue;
        used[u + v] = 1;
        dfs(u + v);
        sequence[top++] = u + v;
    }
}

struct state
{
    int u, v;
};

void dfs1(int u)
{
    stack<state> stk;
    stk.push(state{u, 0});

    while (!stk.empty())
    {
        state node = stk.top();
        stk.pop();

        int u = (node.u & mask) << 1;
        if (used[u + node.v]) continue;

        sequence[top++] = node.u + node.v;
        used[u + node.v] = 1;
        if (node.v == 0) stk.push(state{u, 1});
        stk.push(state{u, node.v});
    }
}

int main(int argc, char *argv[])
{
    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> k;

        bits = 1 << n, mask = (1 << (n - 1)) - 1;
        memset(used, 0, sizeof(int) * bits);
        top = 0;
        
        dfs(0);
        cout << sequence[bits - 1 - k] << '\n';
        
        //dfs1(0);
        //cout << sequence[bits - 1 - k] << '\n';
    }

    return 0;
}
