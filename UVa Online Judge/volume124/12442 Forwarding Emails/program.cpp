// Forwarding Emails
// UVa ID: 12442
// Verdict: Accepted
// Submission Date: 2018-01-29
// UVa Run Time: 0.170s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

const int LENGTH = (1 << 20);

inline int nextChar()
{
    static char buffer[LENGTH], *p = buffer, *end = buffer;
    if (p == end) {
        if ((end = buffer + fread(buffer, 1, LENGTH, stdin)) == buffer) return EOF;
        p = buffer;
    }
    return *p++;
}

inline bool nextInt(int &x)
{
    static char negative = 0, c = nextChar();
    negative = 0, x = 0;
    while ((c < '0' || c > '9') && c != '-') { if (c == EOF) return false; c = nextChar(); }
    if (c == '-') { negative = 1; c = nextChar(); }
    do x = (x << 3) + (x << 1) + c - '0'; while ((c = nextChar()) >= '0');
    if (negative) x = -x;
    return true;
}

int n, u, v, edges[50010] = {0}, visited[50010], marked[50010];

int dfs(int u)
{
    marked[u] = 1;
    
    int cnt = 0;
    visited[u] = 1;
    if (!visited[edges[u]])
        cnt = dfs(edges[u]) + 1;
    visited[u] = 0;

    return cnt;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;

    nextInt(cases);
    for (int c = 1; c <= cases; c++)
    {
        nextInt(n);
        for (int i = 1; i <= n; i++)
        {
            nextInt(u), nextInt(v);
            edges[u] = v;
        }

        memset(marked, 0, (n + 1) * sizeof(int));
        memset(visited, 0, (n + 1) * sizeof(int));

        int maxCnt = 0, maxI = 0;
        for (int i = 1; i <= n; i++)
        {
            if (marked[i]) continue;

            int cnt = dfs(i);

            if (cnt > maxCnt)
            {
                maxCnt = cnt;
                maxI = i;
            }
            if (maxCnt == n) break;
        }
        cout << "Case " << c << ": " << maxI << '\n';
    }

    return 0;
}
