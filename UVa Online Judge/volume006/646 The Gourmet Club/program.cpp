// The Gourmet Club
// UVa ID: 646
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int meeted[16][16], matched[2][16];

void match(string s)
{
    for (int i = 0; i < s.length(); i++)
        for (int j = i + 1; j < s.length(); j++)
        {
            meeted[s[i] - 'A'][s[j] - 'A'] = 1;
            meeted[s[j] - 'A'][s[i] - 'A'] = 1;
        }
}

bool done = false;
void dfs(int i, int j)
{
    if (i == 2)
    {
        done = true;
    }
    if (j == 16) dfs(i + 1, 0);
    else
    {
        for (int k = 0; k < 15; k++)
        {
            if (matched[i][k]) continue;
            
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string combine;
    while (cin >> combine)
    {
        memset(meeted, 0, sizeof(meeted));
        match(combine);
        for (int i = 1; i <= 11; i++)
        {
            cin >> combine;
            match(combine);
        }
        
        done = false;
        memset(matched, 0, sizeof(matched));
        dfs(0, 0);
        
        if (!done) cout << "It is not possible to complete this schedule.\n";
    }

    return 0;
}
