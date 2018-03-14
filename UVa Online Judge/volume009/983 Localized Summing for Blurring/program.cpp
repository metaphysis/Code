// Localized Summing for Blurring
// UVa ID: 983
// Verdict: Accepted
// Submission Date: 2017-03-09
// UVa Run Time: 0.240s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int grid[1001][1001] = {0}, partial[1001][1001] = {0}, N, M;
    int cases = 0;
    
    while (cin >> N >> M)
    {
        if (cases++ > 0) cout << '\n';
        
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                cin >> grid[i][j];
                
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                partial[i][j] = partial[i - 1][j] + partial[i][j - 1] + grid[i][j] - partial[i - 1][j - 1];
                
        long long total = 0;
        
        for (int i = M; i <= N; i++)
            for (int j = M; j <= N; j++)
            {
                int local = partial[i][j] - partial[i - M][j] - partial[i][j - M] + partial[i - M][j - M];
                cout << local << '\n';
                total += local;
            }
            
        cout << total << '\n';
    }
    
    return 0;
}
