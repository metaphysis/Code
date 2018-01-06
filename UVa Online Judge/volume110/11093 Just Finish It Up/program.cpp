// Just Finish It Up
// UVa ID: 11093
// Verdict: Accepted
// Submission Date: 2018-01-06
// UVa Run Time: 0.010s
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

    int available[100010], needed[100010], n;
    int cases;
    
    nextInt(cases);
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";

        nextInt(n);
        
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++) { nextInt(available[i]); sum1 += available[i]; }
        for (int i = 0; i < n; i++) { nextInt(needed[i]); sum2 += needed[i]; }
        
        if (sum1 < sum2) { cout << "Not possible\n"; continue; };

        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (available[i] >= needed[i])
            {
                int remain = 0;
                for (int j = 0; j < n; j++)
                {
                    remain += (available[(i + j) % n] - needed[(i + j) % n]);
                    if (remain < 0) break;
                }
                if (remain >= 0)
                {
                    cout << "Possible from station " << (i + 1) << '\n';
                    found = true;
                    break;
                }
            }
        }
        if (!found) cout << "Not possible\n";
    }

    return 0;
}
