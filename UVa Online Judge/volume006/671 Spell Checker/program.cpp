// Spell checker
// UVa ID: 671
// Verdict: Accepted
// Submission Date: 2017-06-01
// UVa Run Time: 1.380s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int med(string S, string T)
{
    int cells[16][16];

    // 为每个字符串起始位置增加一个空格，将字符串序号和表格序号对齐，方便处理。
    S = ' ' + S, T = ' ' + T;
    int M = S.length() - 1, N = T.length() - 1;

    // 初始化表格。
    cells[0][0] = 0;
    for (int i = 1; i <= M; i++) cells[i][0] = i;
    for (int j = 1; j <= N; j++) cells[0][j] = j;

    // 自底向上动态规划求解。
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
        {
            cells[i][j] = min(cells[i - 1][j], cells[i][j - 1]) + 1;
            if (S[i] == T[j])
                cells[i][j] = min(cells[i][j], cells[i - 1][j - 1]);
            else
                cells[i][j] = min(cells[i][j], cells[i - 1][j - 1] + 1);
        }

    return cells[M][N];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        set<string> words;
        vector<string> dictionary;
        string word;
        
        while (cin >> word, word.front() != '#') words.insert(word), dictionary.push_back(word);
        while (cin >> word, word.front() != '#')
        {
            cout << word;
            if (words.find(word) != words.end())
            {
                cout << " is correct\n";
                continue;
            }
            
            cout << ':';
            
            int l1 = word.size();
            for (auto entry : dictionary)
            {
                int l2 = entry.size();
                if (abs(l1 - l2) >= 2) continue;

                if (med(word, entry) == 1)
                    cout << ' ' << entry;
            }

            cout << '\n';
        }
    }
    
    return 0;
}
