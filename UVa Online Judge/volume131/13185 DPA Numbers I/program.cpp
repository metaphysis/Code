// DPA Numbers I
// UVa ID: 13185
// Verdict: Accepted
// Submission Date: 2022-10-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int sum[1010] = {0};
    for (int i = 1; i <= 1000; i++)
        for (int j = 1; j < i; j++)
            if (i % j == 0)
                sum[i] += j;
    int t, n;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cin >> n;
        if (sum[n] == n) cout << "perfect";
        else if (sum[n] < n)  cout << "deficient";
        else cout << "abundant";
        cout << '\n';
    }
    return 0;
}
