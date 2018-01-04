// Garbage Collection
// UVa ID: 12608
// Verdict: Accepted
// Submission Date: 2017-01-04
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

inline int nextChar()
{
    const int LENGTH = 1048576;
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

    int T, W, N, xi, wi;

    nextInt(T);
    for (int c = 1; c <= T; c++)
    {
        nextInt(W), nextInt(N);
        int dist = 0, loaded = 0, lastx = 0;
        for (int i = 1; i <= N; i++)
        {
            nextInt(xi), nextInt(wi);
            dist += xi - lastx;
            while (true)
            {
                if (wi + loaded > W)
                {
                    dist += 2 * xi;
                    loaded = 0;
                }
                else if (wi + loaded == W)
                {
                    dist += xi;
                    wi = loaded = 0;
                    lastx = 0;
                    break;
                }
                else
                {
                    loaded += wi;
                    lastx = xi;
                    break;
                }
            }
        }
        dist += lastx;
        cout << dist << '\n';
    }

    return 0;
}
