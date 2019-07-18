// Ducci Sequence
// UVa ID: 1594
// Verdict: Accepted
// Submission Date: 2019-07-18
// UVa Run Time: 0.360s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string getDigit(int x)
{
    string d;
    while (d.length() < 3)
    {
        d += (char)('0' + x % 16);
        x /= 16;
    }
    return d;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, tuples[20];
    unordered_set<string> visited;
    string key;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        key.clear();
        for (int i = 0; i < n; i++)
        {
            cin >> tuples[i];
            key += getDigit(tuples[i]);
        }
        visited.clear();
        visited.insert(key);
        while (true)
        {
            tuples[n] = tuples[0];
            key.clear();
            for (int i = 0; i < n; i++)
            {
                tuples[i] = abs(tuples[i + 1] - tuples[i]);
                key += getDigit(tuples[i]);
            }
            if (visited.find(key) != visited.end())
            {
                if (key == string(3 * n, '0')) cout << "ZERO";
                else cout << "LOOP";
                cout << '\n';
                break;
            }
            else visited.insert(key);
        }
    }

    return 0;
}
