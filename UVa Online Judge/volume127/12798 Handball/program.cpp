// Handball
// UVa ID: 12798
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

    int N, M;
    while (cin >> N >> M)
    {
        int T = 0;
        for (int i = 1, goals; i <= N; i++)
        {
            int flag = 1;
            for (int j = 1, goals; j <= M; j++)
            {
                cin >> goals;
                if (goals == 0) flag = 0;
            }
            T += flag;
        }
        cout << T << '\n'; 
    }

    return 0;
}
