// An Easy Problem!
// UVa ID: 10093
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool divisible(string &n, int base)
{
    int r = 0;
    for (auto c : n)
    {
        if (c == ' ' || c == '\t') continue;
        if (c == '+' || c == '-') continue;
        r *= base;
        if (isdigit(c)) r += c - '0';
        if (isupper(c)) r += c - 'A' + 10;
        if (islower(c)) r += c - 'a' + 36;
        r %= (base - 1);
    }
    return r == 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        char base = '0';
        for (auto c : line)
        {
            if (c == ' ' || c == '\t') continue;
            if (c == '+' || c == '-') continue;
            base = max(c, base);
        }

        int from = 0;
        if (isdigit(base)) from = base - '0';
        if (isupper(base)) from = base - 'A' + 10;
        if (islower(base)) from = base - 'a' + 36;
        
        bool found = false;
        for (int i = max(2, from + 1); i <= 62; i++)
            if (divisible(line, i))
            {
                found = true;
                cout << i << '\n';
                break;
            }

        if (!found) cout << "such number is impossible!\n";
    }

    return 0;
}
