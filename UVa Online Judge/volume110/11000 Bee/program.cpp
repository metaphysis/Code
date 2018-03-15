// Bee
// UVa ID: 11000
// Verdict: Accepted
// Submission Date: 2018-03-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long male[46] = {0, 1}, female[46] = {1, 1}, total[46] = {1, 2};
    for (int i = 2; i <= 45; i++)
    {
        male[i] = male[i - 1] + female[i - 1];
        female[i] = female[i - 1] + female[i - 2];
        total[i] = male[i] + female[i];
    }
    
    int n;
    while (cin >> n, n >= 0)
    {
        cout << male[n] << ' ' << total[n] << '\n';
    }

    return 0;
}
