// Dice
// UVa ID: 11959
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

    int exchanged[24][6] = {
        {0, 1, 2, 3, 4, 5}, {0, 1, 3, 4, 5, 2}, {0, 1, 4, 5, 2, 3}, {0, 1, 5, 2, 3, 4},
        {1, 0, 2, 5, 4, 3}, {1, 0, 5, 4, 3, 2}, {1, 0, 4, 3, 2, 5}, {1, 0, 3, 2, 5, 4},
        {2, 4, 1, 3, 0, 5}, {2, 4, 3, 0, 5, 1}, {2, 4, 0, 5, 1, 3}, {2, 4, 5, 1, 3, 0},
        {3, 5, 0, 2, 1, 4}, {3, 5, 2, 1, 4, 0}, {3, 5, 1, 4, 0, 2}, {3, 5, 4, 0, 2, 1},
        {4, 2, 0, 3, 1, 5}, {4, 2, 3, 1, 5, 0}, {4, 2, 1, 5, 0, 3}, {4, 2, 5, 0, 3, 1},
        {5, 3, 0, 4, 1, 2}, {5, 3, 4, 1, 2, 0}, {5, 3, 1, 2, 0, 4}, {5, 3, 2, 0, 4, 1}
    };
    
    
    int cases;
    string dice1, dice2;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> dice1 >> dice2;
        
        bool same = false;
        for (int i = 0; i < 24; i++)
        {
            same = true;
            for (int j = 0; j < 6; j++)
                if (dice1[exchanged[i][j]] != dice2[j])
                {
                    same = false;
                    break;
                }
            if (same) break;
        }
                
        if (same) cout << "Equal\n";
        else cout << "Not Equal\n";
    }
    
    return 0;
}
