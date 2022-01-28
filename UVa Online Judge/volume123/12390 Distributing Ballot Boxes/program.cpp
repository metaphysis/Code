// Distributing Ballot Boxes
// UVa ID: 12390
// Verdict: Accepted
// Submission Date: 2022-01-28
// UVa Run Time: 0.200s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int N, B, P[500010];
    while (cin >> N >> B)
    {
        if (N == -1) break;
        int low = 1, high = 0;
        for (int i = 0; i < N; i++)
        {
            cin >> P[i];
            high = max(high, P[i]);
        }
        int middle, r;
        while (low <= high)
        {
            middle = (low + high) >> 1;
            long long b = 0;
            int flag = 1;
            for (int i = 0; i < N; i++)
            {
                b += P[i] / middle + (P[i] % middle != 0);
                if (b > B)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag) 
            {
                r = middle;
                high = middle - 1;
            }
            else low = middle + 1;
        }
        cout << r << '\n';
    }
    return 0;
}
