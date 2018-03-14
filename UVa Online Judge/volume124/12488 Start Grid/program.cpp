// Start Grid
// UVa ID: 12488
// Verdict: Accepted
// Submission Date: 2017-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, start[25], end[25];
    
    while (cin >> n)
    {
        for (int i = 1; i <= n; i++)
            cin >> start[i];
        for (int i = 1; i <= n; i++)
            cin >> end[i];
            
        int overtakes = 0;
        for (int i = 1; i <= n; i++)
        {
            int rank;
            for (int j = 1; j <= n; j++)
                if (start[j] == end[i])
                    rank = j;
                    
            while (rank > i)
            {
                swap(start[rank], start[rank - 1]);
                rank--;
                overtakes++;
            }
        }
        
        cout << overtakes << '\n';
    }
    
    return 0;
}
