// Three-Square
// UVa ID: 11342
// Verdict: Accepted
// Submission Date: 2017-11-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int flag[50001] = {0}, square[50001][3];
    
    int up = sqrt(50000) + 1;
    for (int i = 0; i < up; i++)
        for (int j = i; j < up; j++)
            for (int k = j; k < up; k++)
            {
                int s = i * i + j * j + k * k;
                if (s > 50000 || flag[s]) continue;
                flag[s] = 1, square[s][0] = i, square[s][1] = j, square[s][2] = k;
            }
            
    int cases, n;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        if (flag[n])
        {
            for (int i = 0; i < 3; i++)
            {
                if (i) cout << ' ';
                cout << square[n][i];
            }
            cout << '\n';
        }
        else cout << "-1\n";
    }
    
    return 0;
}
