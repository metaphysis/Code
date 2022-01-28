// Orchestral Scores
// UVa ID: 13177
// Verdict: Accepted
// Submission Date: 2022-01-28
// UVa Run Time: 0.050s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int p, n, m[100010];
    while (cin >> p >> n)
    {
        int low = 1, high = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> m[i];
            high = max(high, m[i]);
        }
        int middle, r;
        while (low <= high)
        {
            middle = (low + high) >> 1;
            int flag = 1, s = 0;
            for (int i = 0; i < n; i++)
            {
                s += m[i] / middle + (m[i] % middle != 0);
                if (s > p)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                r = middle;
                high = middle - 1;
            }
            else low = middle + 1;
        }
        cout << r << '\n';
    }
    return 0;
}
