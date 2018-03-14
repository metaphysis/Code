// France '98
// UVa ID: 542
// Verdict: Accepted
// Submission Date: 2016-09-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string names[16];
    double possibility[16][16] = {0}, win[16][5] = {0};

    for (int i = 0; i < 16; i++)
        cin >> names[i];
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
            cin >> possibility[i][j];
        win[i][0] = 100.0;
        for (int j = 1; j <= 4; j++)
            win[i][j] = 0.0;
    }
    
    int group = 2, last_group = 1;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
                if (((j / group) == (k / group)) && ((j / last_group) != (k / last_group)))
                    win[j][i] += win[k][i - 1] * possibility[j][k] / 10000.0;
            
            win[j][i] *= win[j][i - 1];
        }
        
        last_group = group;
        group *= 2;
    }
    
    for (int i = 0; i < 16; i++)
    {
        cout << setw(10) << left << names[i];
        cout << " p=";
        cout << fixed << setprecision(2) << win[i][4];
        cout << "%\n";
    }
    
	return 0;
}
