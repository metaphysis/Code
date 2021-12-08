// D as in Daedalus
// UVa ID: 13007
// Verdict: Accepted
// Submission Date: 2021-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int N, M, Ci[32], B;
    while (cin >> N >> M)
    {
        int extra = 0;
        for (int i = 0; i < M; i++)
        {
            cin >> B;
            int sum = 0;
            for (int j = 0; j < N; j++)
            {
                cin >> Ci[j];
                sum += Ci[j];
            }
            int win1 = 0, win2 = 0;
            if (sum <= B) win1 = Ci[0];
            sum -= Ci[0];
            Ci[0] = 1;
            while (Ci[0] <= 10000)
            {
                if (sum + Ci[0] > B) break;
                win2 = Ci[0];
                Ci[0] *= 10;
            }
            if (win2 > win1) extra += win2 - win1;
        }
        cout << extra << '\n';
    }
    return 0;
}
