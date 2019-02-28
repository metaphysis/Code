// Dangerous Dive
// UVa ID: 12650
// Verdict: Accepted
// Submission Date: 2019-02-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int flag[10010];
    int N, R;
    while (cin >> N >> R)
    {
        memset(flag, 0, sizeof(flag));
        int returned = 0;
        for (int i = 1, plate; i <= R; i++)
        {
            cin >> plate;
            flag[plate] = 1;
            returned++;
        }
        if (returned == N) cout << "*\n";
        else
        {
            for (int i = 1; i <= N; i++)
                if (!flag[i])
                    cout << i << ' ';
            cout << '\n';
        }
    }
    return 0;
}
