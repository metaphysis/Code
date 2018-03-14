// Ant's Shopping Mall
// UVa ID: 12498
// Verdict: Accepted
// Submission Date: 2017-11-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int R, C, mall[60][60], INF = 0x3fffffff;
    char v;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> R >> C;
        
        bool blocked = false;
        for (int i = 1; i <= R; i++)
        {
            int row = 0;
            for (int j = 1; j <= C; j++)
            {
                cin >> v;
                mall[i][j] = v - '0';
                row += mall[i][j];
            }
            if (row == C) blocked = true;
        }
            
        cout << "Case " << c << ": ";
        if (blocked)
        {
            cout << "-1\n";
            continue;
        }
        
        int lowest = INF;
        for (int i = 1; i <= C; i++)
        {
            int current = 0;
            for (int j = 1; j <= R; j++)
            {
                if (mall[j][i])
                {
                    int down = i, up = i;
                    while (down >= 1 && mall[j][down])
                        down--;
                    while (up <= C && mall[j][up])
                        up++;
                        
                    if (down < 1) down = INF;
                    if (up > C) up = INF;
                    
                    current += min(abs(i - down), abs(up - i));
                }
            }
            
            lowest = min(lowest, current);
        }
        
        cout << lowest << '\n';
    }
    
    return 0;
}
