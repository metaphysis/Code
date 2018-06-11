// Another Lottery
// UVa ID: 11628
// Verdict: Accepted
// Submission Date: 2018-06-11
// UVa Run Time: 0.030s
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

    int n, m, xi[10010];
    
    while (true)
    {
        nextInt(n), nextInt(m);
        if (n == 0) break;

        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                nextInt(xi[i]);
            sum += xi[i];
        }
        for (int i = 1; i <= n; i++)
        {
            int g = __gcd(xi[i], sum);
            cout << xi[i] / g << " / " << sum / g << '\n';
        }
    }

    return 0;
}
