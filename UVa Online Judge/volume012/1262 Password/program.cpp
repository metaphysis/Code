// Password
// UVa ID: 1262
// Verdict: Accepted
// Submission Date: 2017-11-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int k, finished;
vector<char> grid1[5], grid2[5];
string password(5, '0');

void dfs(int depth)
{
    if (finished) return;
    
    if (depth == 5)
    {
        if (--k == 0)
        {
            cout << password << '\n';
            finished = 1;
        }
        return;
    }
    
    int i = 0, j = 0, upi = grid1[depth].size(), upj = grid2[depth].size();
    
    while (i < upi && j < upj)
    {
        if (grid1[depth][i] != grid2[depth][j])
        {
            if (grid1[depth][i] < grid2[depth][j])
                i++;
            else
                j++;
            continue;
        }
        
        password[depth] = grid1[depth][i];

        dfs(depth + 1);

        i++, j++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int cases;
    char letter;
    
    cin >> cases;
    for (int c1 = 1; c1 <= cases; c1++)
    {
        cin >> k;
        
        for (int i = 0; i < 5; i++)
        {
            grid1[i].clear();
            grid2[i].clear();
        }
        
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 5; j++)
            {
                cin >> letter;
                grid1[j].push_back(letter);
            }

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 5; j++)
            {
                cin >> letter;
                grid2[j].push_back(letter);
            }        

        for (int i = 0; i < 5; i++)
        {
            sort(grid1[i].begin(), grid1[i].end());
            grid1[i].erase(unique(grid1[i].begin(), grid1[i].end()), grid1[i].end());
            
            sort(grid2[i].begin(), grid2[i].end());
            grid2[i].erase(unique(grid2[i].begin(), grid2[i].end()), grid2[i].end());
        }
            
        finished = 0;
        fill(password.begin(), password.end(), '0');
        dfs(0);
        if (!finished) cout << "NO\n";
    }

    return 0;
}
