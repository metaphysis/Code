// Arithmetic
// UVa ID: 11952
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long convert(string s, int base)
{
    long long n = 0;
    for (int i = 0; i < s.length(); i++)
        n = n * (long long)base + (long long)(s[i] - '0');
    return n;
}

bool allOne(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (s[i] != '1')
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string n1, plus, n2, equals, n3;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n1 >> plus >> n2 >> equals >> n3;

        // Special case.
        if (allOne(n1) && allOne(n2) && allOne(n3) && n3.length() == n1.length() + n2.length())
        {
            cout << "1\n";
            continue;
        }
        
        // Find minimum base.
        string all = n1 + n2 + n3;
        char radix = '0';
        for (auto d : all) radix = max(radix, d);

        // Check from minimum base to 18.
        bool printed = false;
        for (int i = max(2, (radix - '0' + 1)); i <= 18; i++)
        {
            long long cc = convert(n3, i);
            long long aa = convert(n1, i);
            long long bb = convert(n2, i);
            if (aa + bb == cc)
            {
                cout << i << '\n';
                printed = true;
                break;
            }
        }

        // None base valid.
        if (!printed) cout << "0\n";
    }

    return 0;
}
