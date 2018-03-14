// The Dragon of Loowater
// UVa ID: 11292
// Verdict: Accepted
// Submission Date: 2017-10-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, height1[20010], height2[20010];
    
    while (cin >> n >> m, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> height1[i];
        for (int i = 0; i < m; i++)
            cin >> height2[i];

        sort(height1, height1 + n);
        sort(height2, height2 + m);
        
        int x = 0, y = 0;
        long long coins = 0;
        while (x < n && y < m)
        {
            if (height2[y] >= height1[x])
            {
                coins += height2[y];
                x++, y++;
            }
            else
                y++;
        }
        if (x < n)
            cout << "Loowater is doomed!\n";
        else
            cout << coins << '\n';
    }
    
    return 0;
}
