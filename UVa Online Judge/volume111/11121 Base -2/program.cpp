// Base -2
// UVa ID: 11121
// Verdict: Accepted
// Submission Date: 2018-03-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, q, r;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case #" << c << ": ";
        cin >> n;
        vector<int> binary;
        while (n)
        {
            q = n / (-2);
            r = n - (-2) * q;

            if (r < 0)
            {
                binary.push_back(1);
                n = ++q;
            }
            else
            {
                binary.push_back(r);
                n = q;
            }
        }
        if (binary.size() == 0) binary.push_back(0);
        reverse(binary.begin(), binary.end());
        for (auto b : binary) cout << b;
        cout << '\n';
    }

    return 0;
}
