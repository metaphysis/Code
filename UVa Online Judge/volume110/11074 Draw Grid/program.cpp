// Draw Grid
// UVa ID: 11074
// Verdict: Accepted
// Submission Date: 2018-03-24
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char board[848][848];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, S, T, N;
    while (cin >> S >> T >> N, S > 0)
    {
        int width = (S + T) * N + T;
        cout << "Case " << ++cases << ":\n";
        for (int n = 0; n < N; n++)
        {
            for (int i = 0; i < T; i++)
            {
                for (int j = 0; j < width; j++) cout << '*';
                cout << '\n';
            }
            for (int i = 0; i < S; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    for (int t = 0; t < T; t++) cout << '*';
                    for (int s = 0; s < S; s++) cout << '.';
                }
                for (int t = 0; t < T; t++) cout << '*';
                cout << '\n';
            }
        }
        for (int i = 0; i < T; i++)
        {
            for (int j = 0; j < width; j++) cout << '*';
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
