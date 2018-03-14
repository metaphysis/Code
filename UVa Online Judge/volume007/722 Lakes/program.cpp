// Lakes
// UVa ID: 722
// Verdict: Accepted
// Submission Date: 2017-03-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int water = 0, r = 0, c = 0, rt = 0, ct = 0;;
char grid[110][110];
        
void flood_fill(int r, int c)
{
    if (r >= 0 && r < rt && c >= 0 && c < ct && grid[r][c] == '0')
    {
        water++;
        grid[r][c] = '1';
        flood_fill(r - 1, c);
        flood_fill(r + 1, c);
        flood_fill(r, c - 1);
        flood_fill(r, c + 1);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int cases = 0;
    string row, column, line;
    
    cin >> cases;
    for (int k = 1; k <= cases; k++)
    {
        cin >> row >> column;
        r = stoi(row), c = stoi(column);
        
        cin.ignore(1024, '\n');
        
        rt = 0;
        memset(grid, 0, sizeof(grid));
        
        while (getline(cin, line), line.length() > 0)
        {
            for (int i = 0; i < line.length(); i++)
                grid[rt][i] = line[i];
            rt++, ct = line.length();
        }
        
        water = 0;
        flood_fill(r - 1, c - 1);
        
        if (k > 1) cout << '\n';
        cout << water << '\n';
    }
    
    return 0;
}
