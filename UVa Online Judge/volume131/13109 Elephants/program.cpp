// Elephants
// UVa ID: 13109
// Verdict: Accepted
// Submission Date: 2018-04-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, weight[100001], M, W;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> M >> W;
        for (int i = 0; i < M; i++)
            cin >> weight[i];
        sort(weight, weight + M);
        bool printed = false;
        for (int i = 0; i < M; i++)
            if (W >= weight[i])
                W -= weight[i];
            else
            {
                cout << i << '\n';
                printed = true;
                break;
            }
        if (!printed) cout << M << '\n';
    }

    return 0;
}
