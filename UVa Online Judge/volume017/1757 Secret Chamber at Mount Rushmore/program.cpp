// Secret Chamber at Mount Rushmore
// UVa ID: 1757
// Verdict: Accepted
// Submission Date: 2017-06-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int m, n;
    bool linked[32][32];
    char a, b;
    string word1, word2;
    
    while (cin >> m >> n)
    {
        memset(linked, false, sizeof(linked));
        
        for (int i = 0; i < 26; i++)
            linked[i][i] = true;

        for (int i = 0; i < m; i++)
        {
            cin >> a >> b;
            linked[a - 'a'][b - 'a'] = true;
        }
        
        for (int k = 0; k < 26; k++)
            for (int i = 0; i < 26; i++)
                for (int j = 0; j < 26; j++)
                    linked[i][j] = linked[i][j] || (linked[i][k] && linked[k][j]);

        for (int i = 0; i < n; i++)
        {
            cin >> word1 >> word2;
            
            if (word1 == word2)
            {
                cout << "yes\n";
                continue;
            }
            
            if (word1.length() != word2.length())
            {
                cout << "no\n";
                continue;
            }
            
            bool connected = true;
            for (int j = 0; j < word1.length(); j++)
                if (!linked[word1[j] - 'a'][word2[j] - 'a'])
                {
                    connected = false;
                    break;
                }
            cout << (connected ? "yes" : "no") << '\n';
        }
    }
    
    return 0;
}
