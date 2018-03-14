// Passwords
// UVa ID: 628
// Verdict: Accepted
// Submission Date: 2016-08-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, m, password[260];
string dictionary[110];

void backtrack(string rule, int depth)
{
    if (depth == rule.length())
    {
        for (int i = 0; i < rule.length(); i++)
        {
            if (password[i] >= 0)
                cout << dictionary[password[i]];
            else
                cout << (char)('0' + password[i] + 10);
        }
        cout << '\n';
    }
    else
    {
        if (rule[depth] == '#')
        {
            for (int j = 0; j < n; j++)
            {
                password[depth] = j;
                backtrack(rule, depth + 1);
            }
        }
        else
        {
            for (int j = 0; j <= 9; j++)
            {
                password[depth] = j - 10;
                backtrack(rule, depth + 1);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string rule;
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
            cin >> dictionary[i];
        
        cout << "--\n";
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> rule;
            for (int j = 0; j < rule.length(); j++)
                if (rule[j] == '0')
                    rule[j] = '$';
            
            backtrack(rule, 0);
        }
    }
    
	return 0;
}
