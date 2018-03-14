// The Monkey and the Oiled Bamboo
// UVa ID: 12032
// Verdict: Accepted
// Submission Date: 2017-11-28
// UVa Run Time: 0.040s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int rungs[100010] = {0}, n;

bool possible(int x)
{
    static int diff;
    for (int i = 1; i <= n; i++)
    {
        diff = rungs[i] - rungs[i - 1];
        if (x > diff) continue;
        if (x == diff) x--;
        else return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c1 = 1; c1 <= cases; c1++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> rungs[i];

        int left = 1, right = 10000000, middle;
        while (left < right)
        {
            middle = (left + right) / 2;
            if (possible(middle)) right = middle;
            else left = middle + 1;
        }
        cout << "Case " << c1 << ": " << (left + right) / 2 << '\n';
    }

    return 0;
}
