// Delivery Debacle
// UVa ID: 11310
// Verdict: Accepted
// Submission Date: 2018-06-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long cnt[41] = {1, 1, 5};
    for (int i = 3; i <= 40; i++)
        cnt[i] = cnt[i - 1] + 4 * cnt[i - 2] + 2 * cnt[i - 3];

    int cases, n;
    cin >> cases;
    while (cases--)
    {
        cin >> n;
        cout << cnt[n] << '\n';
    }

    return 0;
}
