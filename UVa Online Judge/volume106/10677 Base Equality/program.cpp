// Base Equality
// UVa ID: 10677
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long stringToNumber(vector<int> s, int base)
{
    long long r = 0;
    for (auto d : s) r = r * base + d;
    return r;
}

vector<int> numberToString(int n, int base)
{
    vector<int> s;
    while (n)
    {
        s.push_back(n % base);
        n /= base;
    }
    if (s.size() == 0) s.push_back(0);
    reverse(s.begin(), s.end());
    return s;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, B1, B2, r1, r2;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> B1 >> B2 >> r1 >> r2;
        bool found = false;
        for (int i = r2 - 1; i > r1; i--)
        {
            vector<int> s = numberToString(i, B1);
            long long k1 = stringToNumber(s, B1);
            long long k2 = stringToNumber(s, B2);
            if (k2 % k1 == 0)
            {
                cout << i << '\n';
                found = true;
                break;
            }
        }
        if (!found) cout << "Non-existent.\n";
    }

    return 0;
}
