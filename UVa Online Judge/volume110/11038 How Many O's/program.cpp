// How Many O's
// UVa ID: 11038
// Verdict: Accepted
// Submission Date: 2022-10-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long getCount(long long n)
{
    if (n == -1) return 0;
    string nn = to_string(n);
    long long ret = 0, pow = 1;
    for (int i = nn.length() - 1; i >= 1; i--) {
        if (nn[i] - '0') ret += stoll(nn.substr(0, i)) * pow;
        else {
            ret += (stoll(nn.substr(0, i)) - 1) * pow + 1;
            if (i < nn.length() - 1) ret += stoll(nn.substr(i + 1));
        }
        pow *= 10;
    }
    return ret + 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long m, n;
    while (cin >> m >> n) {
        if (m == -1) break;
        cout << getCount(n) - getCount(m - 1) << '\n';
    }

    return 0;
}
