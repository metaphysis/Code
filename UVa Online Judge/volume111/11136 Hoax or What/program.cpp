// Hoax or What
// UVa ID: 11136
// Verdict: Accepted
// Submission Date: 2018-01-07
// UVa Run Time: 0.640s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

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

    int n, k, money;
    while (true)
    {
        nextInt(n);
        if (n == 0) break;

        multiset<int> bills;
        long long paid = 0;
        for (int i = 1; i <= n; i++)
        {
            nextInt(k);
            for (int j = 1; j <= k; j++)
            {
                nextInt(money);
                bills.insert(money);
            }
            multiset<int>::iterator end = bills.end(); end--;
            paid += *end - *bills.begin();
            bills.erase(end);
            bills.erase(bills.begin());
        }
        cout << paid << '\n';
    }

    return 0;
}
