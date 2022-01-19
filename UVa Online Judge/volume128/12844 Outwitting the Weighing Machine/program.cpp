// Outwitting the Weighing Machine
// UVa ID: 12844
// Verdict: Accepted
// Submission Date: 2022-01-19
// UVa Run Time: 0.090s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int w[5], W[12];

bool validate()
{
    static int T[12];
    int cnt = 0;
    for (int i = 0; i < 5; i++)
        for (int j = i + 1; j < 5; j++)
            T[cnt++] = w[i] + w[j];
    sort(T, T + 10);
    for (int i = 0; i < 10; i++)
        if (W[i] != T[i])
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        for (int i = 0; i < 10; i++)
            cin >> W[i];
        sort(W, W + 10);
        int working = 1;
        for (int i = 1; i <= 400 && working; i++)
        {
            w[0] = i, w[1] = W[0] - i, w[2] = W[1] - i;
            if (w[0] > w[1] || w[0] > w[2] || w[1] > w[2]) continue;
            for (int j = w[2]; j <= 400 && working; j++)
            {
                w[3] = j, w[4] = W[9] - j;
                if (w[3] > w[4]) continue;
                if (validate()) working = 0;
            }
        }
        cout << "Case " << cs << ':';
        for (int i = 0; i < 5; i++) cout << ' ' << w[i];
        cout << '\n';
    }
    return 0;
}
