// Football
// UVa ID: 12673
// Verdict: Accepted
// Submission Date: 2019-07-23
// UVa Run Time: 0.060s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, G, D[100010];
    while (cin >> N >> G)
    {
        for (int i = 0, S, R; i < N; i++)
        {
            cin >> S >> R;
            D[i] = R - S;
        }
        sort(D, D + N);
        int S = 0;
        for (int i = 0; i < N && G >= 0; i++)
        {
            if (D[i] < 0) S += 3;
            else
            {
                if (G >= D[i] + 1) S += 3, G -= D[i] + 1;
                else
                {
                    if (G >= D[i]) S += 1, G -= D[i];
                    else break;
                }
            }
        }
        cout << S << '\n';
    }
    return 0;
}
