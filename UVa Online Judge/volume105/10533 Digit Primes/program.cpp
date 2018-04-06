// Digit Primes
// UVa ID: 10533
// Verdict: Accepted
// Submission Date: 2018-04-06
// UVa Run Time: 0.060s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1 << 20);

int number[MAXN + 1] = {}, primes[MAXN + 1] = {}, cnt = 0;

inline int nextChar()
{
    static char buffer[MAXN], *p = buffer, *end = buffer;
    if (p == end) {
        if ((end = buffer + fread(buffer, 1, MAXN, stdin)) == buffer) return EOF;
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

    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i, number[i] = 1;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (!(i % primes[j])) break;
        }
    }

    for (int i = 2; i < MAXN; i++)
        if (number[i])
        {
            int d = 0, n = i;
            while (n) d += n % 10, n /= 10;
            number[i] = number[i - 1] + binary_search(primes, primes + cnt, d);
        }
        else number[i] = number[i - 1];

    //for (int i = 2; i * i < MAXN; i++)
    //    if (!number[i])
    //        for (int j = i * i; j < MAXN; j += i)
    //            number[j] = 1;
    //for (int i = 2; i < MAXN; i++)
    //    if (!number[i])
    //        primes[cnt++] = i;

    //for (int i = 2; i < MAXN; i++)
    //    if (!number[i])
    //    {
    //        int d = 0, n = i;
    //        while (n) d += n % 10, n /= 10;
    //        number[i] = number[i - 1] + binary_search(primes, primes + cnt, d);
    //    }
    //    else number[i] = number[i - 1];

    int cases, t1, t2;
    nextInt(cases);
    for (int c = 1; c <= cases; c++)
    {
        nextInt(t1), nextInt(t2);
        cout << number[t2] - number[t1 - 1] << '\n';
    }

    return 0;
}
