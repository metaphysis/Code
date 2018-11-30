// Naughty Sleepy Boys
// UVa ID: 10427
// Verdict: Accepted
// Submission Date: 2018-11-30
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int digits[14000000] = {};

inline int getCount(int n)
{
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int last = 1;
    while (true)
    {
        digits[last] = digits[last - 1] + getCount(last);
        if (digits[last++] > 100000000) break;
    }

    int N;
    while (cin >> N)
    {
        int n = lower_bound(digits, digits + last, N) - digits;
        string s = to_string(n);
        cout << s[(getCount(n) - 1) - (digits[n] - N)] << '\n';
    }

    return 0;
}
