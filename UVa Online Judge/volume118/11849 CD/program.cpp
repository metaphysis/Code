// CD
// UVa ID: 11849
// Verdict: Accepted
// Submission Date: 2018-01-07
// UVa Run Time: 0.740s
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

    int n, m, catalog, maxCatalog;
    while (true)
    {
        nextInt(n), nextInt(m);
        if (n == 0 && m == 0) break;
        unordered_set<int> cds;
        catalog = -1;
        for (int i = 0; i < n; i++)
        {
            nextInt(catalog);
            cds.insert(catalog);
        }
        maxCatalog = catalog;
        int copy = 0;
        for (int i = 0; i < m; i++)
        {
            nextInt(catalog);
            if (catalog <= maxCatalog && cds.find(catalog) != cds.end()) copy++;
        }
        cout << copy << '\n';
    }

    return 0;
}
