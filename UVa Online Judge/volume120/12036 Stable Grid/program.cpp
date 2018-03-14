// Stable Grid
// UVa ID: 12036
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

    int cases, n, number, cnt[110];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";
        memset(cnt, 0, sizeof(cnt));
        cin >> n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                cin >> number;
                cnt[number]++;
            }
        int maxCount = *max_element(cnt, cnt + 110);
        if (maxCount > n) cout << "no";
        else cout << "yes";
        cout << '\n';
    }

    return 0;
}
