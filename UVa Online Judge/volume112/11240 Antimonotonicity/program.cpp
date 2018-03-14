// Antimonotonicity
// UVa ID: 11240
// Verdict: Accepted
// Submission Date: 2018-01-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

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

    const int DES = 0, INC = 1;
    int cases, n, fred, last, direction, length;
    
    nextInt(cases);
    for (int c = 1; c <= cases; c++)
    {
        nextInt(n);
        last = direction = length = 0;
        for (int i = 1; i <= n; i++)
        {
            nextInt(fred);
            if (last < fred)
            {
                if (direction == DES)
                {
                    length++;
                    direction = INC;
                }
            }
            else
            {
                if (direction == INC)
                {
                    length++;
                    direction = DES;
                }
            }
            last = fred;
        }
        cout << length << '\n';
    }

    return 0;
}
