// As Long as I Learn, I Live
// UVa ID: 12376
// Verdict: Accepted
// Submission Date: 2018-01-29
// UVa Run Time: 0.000s
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, units[110], edges[110], n, m, u, v, t;
    
    nextInt(cases);
    for (int c = 1; c <= cases; c++)
    {
        nextInt(n), nextInt(m);
        memset(edges, -1, sizeof(edges));
        for (int i = 0; i < n; i++)
            nextInt(units[i]);
            
        for (int i = 0; i < m; i++)
        {
            nextInt(u), nextInt(v);
            if (edges[u] < 0 || units[v] > units[edges[u]])
                edges[u] = v;
        }
        u = t = 0;
        do
        {
            u = edges[u];
            t += units[u];
        } while (edges[u] >= 0);
        cout << "Case " << c << ": " << t << ' ' << u << '\n';
    }

    return 0;
}
