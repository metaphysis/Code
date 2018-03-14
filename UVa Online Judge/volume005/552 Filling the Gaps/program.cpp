// Filling the Gaps
// UVa ID: 552
// Verdict: Accepted
// Submission Date: 2017-05-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int visited[65536];

void backtrack(int i, int v, string &pattern)
{
    if (i >= pattern.length())
        visited[v] = 1;
    else
    {
        v *= 2;
        if (pattern[i] == '*')
        {
            backtrack(i + 1, v, pattern);
            backtrack(i + 1, v + 1, pattern);
            
        }
        else
        {
            v += pattern[i] - '0';
            backtrack(i + 1, v, pattern);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int length, n;
    
    while (cin >> length >> n)
    {
        if (length == 0 && n == 0)
        {
            cout << "YES 0\n";
            break;
        }
        
        vector<string> words;
        vector<int> ids;

        string word;
        for (int i = 1; i <= n; i++)
        {
            cin >> word;
            
            int id = 0;
            for (int j = 0; j < word.size(); j++)
            {
                id *= 2;
                if (word[j] == '*') id += 1;
            }
                    
            words.push_back(word);
            ids.push_back(id);
        }
        
        sort(ids.begin(), ids.end());
        
        bool duplicated = false;
        for (int i = 0; i < ids.size() - 1; i++)
            if (ids[i] == ids[i + 1])
            {
                duplicated = true;
                break;
            }
            
        if (duplicated)
        {
            cout << "NO\n";
            continue;
        }
        
        memset(visited, 0, sizeof(visited));
        
        for (int i = 0; i < words.size(); i++)
            backtrack(0, 0, words[i]);

        int total = pow(2, length), appeared = 0;
        for (int i = 0; i < total; i++)
            appeared += visited[i];

        cout << "YES " << appeared << '\n';
    }

    return 0;
}
