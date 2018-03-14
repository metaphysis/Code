// Garbage Heap
// UVa ID: 10755
// Verdict: Accepted
// Submission Date: 2017-11-18
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, A, B, C;
    long long cube[21][21][21], sum[21][21][21];
    
    cin >> cases;
    for (int c1 = 1; c1 <= cases; c1++)
    {
        cin >> A >> B >> C;
        
        for (int a = 1; a <= A; a++)
            for (int b = 1; b <= B; b++)
                for (int c = 1; c <= C; c++)
                    cin >> cube[a][b][c];
                    
        memset(sum, 0, sizeof(sum));
        for (int a = 1; a <= A; a++)
            for (int b = 1; b <= B; b++)
                for (int c = 1; c <= C; c++)
                    sum[a][b][c] = sum[a][b - 1][c] + sum[a][b][c - 1] - sum[a][b - 1][c - 1] + cube[a][b][c];
                    
        long long maxv = -0x3fffffffffffffff;
        
        for (int b = 1; b <= B; b++)
            for (int c = 1; c <= C; c++)
                for (int h = 0; h <= B - b; h++)
                    for (int w = 0; w <= C - c; w++)
                    {
                        long long s1 = sum[1][b + h][c + w] - sum[1][b + h][c - 1] - sum[1][b - 1][c + w] + sum[1][b - 1][c - 1];
                        long long maxr = s1, currents = s1;
                        for (int a = 2; a <= A; a++)
                        {
                            long long s2 = sum[a][b + h][c + w] - sum[a][b + h][c - 1] - sum[a][b - 1][c + w] + sum[a][b - 1][c - 1];
                            currents = max(s2, currents + s2);
                            maxr = max(maxr, currents);
                        }
                        maxv = max(maxv, maxr);
                    }
              
        if (c1 > 1) cout << '\n';      
        cout << maxv << '\n';
    }

    return 0;
}
