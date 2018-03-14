// Boxes of Chocolates
// UVa ID: 10489
// Verdict: Accepted
// Submission Date: 2018-03-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, B, K;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> B;
        int r = 0;
        for (int i = 1; i <= B; i++)
        {
            cin >> K;
            int t = 1;
            for (int j = 1, b; j <= K; j++)
            {
                cin >> b;
                t *= b;
                t %= N;
            }
            r += t;
            r %= N;
        }
        cout << r << '\n';
    }

    return 0;
}
