// Homogeneous Squares
// UVa ID: 11055
// Verdict: Accepted
// Submission Date: 2018-03-14
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cell[1010][1010];

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

    int n;
    while (nextInt(n), n > 0)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                nextInt(cell[i][j]);

        // Make first row all zeros.
        for (int i = 1; i < n; i++)
            for (int j = 0; j < n; j++)
                cell[i][j] -= cell[0][j];

        // Make first column all zeros.
        for (int i = 1; i < n; i++)
            for (int j = 1; j < n; j++)
                cell[i][j] -= cell[i][0];

        // Check all cells if zero or not.
        bool homogeneous = true;
        for (int j = 1; j < n; j++)
            for (int i = 1; i < n; i++)
                if (cell[i][j])
                {
                    homogeneous = false;
                    goto print;
                }

        print:
        if (homogeneous) cout << "homogeneous";
        else cout << "not homogeneous";
        cout << '\n';
    }

    return 0;
}
