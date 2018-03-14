// Test
// UVa ID: 629
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int used[10][26], matched[10][10], finished = 0;
int n;

void backtrack(int u)
{
    for (int v = u + 1; v < n; v++)
    {
        if (matched[u][v])
        {
            for (int i = 0; i < 26; i++)
            {
                if (
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n)
    {
        char diff;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                cin >> diff;
                if (diff == '-') matched[i][j] = 1;
            }
            
        finished = 0;
        memset(used, 0, sizeof(used));
        backtrack(0);
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 26; j++)
                if (used[i][j])
                    cout << (char)('a' + j);
            cout << '\n';
        }
        cout << "_____\n";
    }
    
    return 0;
}
