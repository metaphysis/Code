// The path in the colored field
// UVa ID: 10102
// Verdict: Accepted
// Submission Date: 2017-11-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int x1[4000], y1[4000], x3[4000], y3[4000];
    int cnt1, cnt2;
    int n;
    char color;

    while (cin >> n)
    {
        cnt1 = cnt2 = 0;
        
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> color;
                if (color == '1') x1[cnt1] = i, y1[cnt1] = j, cnt1++;
                if (color == '3') x3[cnt2] = i, y3[cnt2] = j, cnt2++;
            }
            
        int steps = 0;
        for (int i = 0; i < cnt1; i++)
        {
            int longest = 0x3fffffff;
            for (int j = 0; j < cnt2; j++)
                longest = min(longest, abs(x1[i] - x3[j]) + abs(y1[i] - y3[j]));
            steps = max(steps, longest);
        }
        cout << steps << '\n';
    }
    
    return 0;
}
