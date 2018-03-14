// Bangla Numbers
// UVa ID: 10101
// Verdict: Accpeted
// Submission Date: 2018-03-04
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<string> convert(long long n)
{
    vector<string> parts;
    if (n < 100)
    {
        parts.push_back(to_string(n));
        return parts;
    }

    if (n >= 10000000)
    {
        long long r = n / 10000000;
        vector<string> next = convert(r);
        for (auto p : next)
            parts.push_back(p);
        parts.push_back("kuti");
        n %= 10000000;
    }
    if (n >= 100000)
    {
        parts.push_back(to_string(n / 100000) + " lakh");
        n %= 100000;
    }
    if (n >= 1000)
    {
        parts.push_back(to_string(n / 1000) + " hajar");
        n %= 1000;
    }
    if (n >= 100)
    {
        parts.push_back(to_string(n / 100) + " shata");
        n %= 100;
    }
    if (n)
        parts.push_back(to_string(n));
    return parts;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    
    long long n;
    int cases = 0;
    while (cin >> n)
    {
        cases++;
        cout << setw(4) << right << cases << ".";
        vector<string> parts = convert(n);
        for (auto p : parts) cout << ' ' << p;
        cout << '\n';
    }

    return 0;
}
