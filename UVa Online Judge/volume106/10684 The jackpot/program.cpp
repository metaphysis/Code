// The jackpot
// UVa ID: 10684
// Verdict: Accepted
// Submission Date: 2017-11-01
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, k;
    while (cin >> n, n > 0)
    {
        int maxSum = 0, currentSum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> k;
            currentSum = max(k, currentSum + k);
            maxSum = max(maxSum, currentSum);
        }
        if (maxSum > 0) cout << "The maximum winning streak is " << maxSum << ".\n";
        else cout << "Losing streak.\n";
    }
    
    return 0;
}
