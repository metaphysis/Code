// Alignment of Code
// UVa ID: 1593
// Verdict: Accepted
// Submission Date: 2022-10-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    vector<string> lines[1010];
    int width[1010] = {0};
    string line, word;
    int cntOfLines = 0;
    while (getline(cin, line))
    {
        istringstream iss(line);
        int cntOfWords = 0;
        while (iss >> word)
        {
            lines[cntOfLines].push_back(word);
            width[cntOfWords] = max(width[cntOfWords], int(word.length()));
            cntOfWords++;
        }
        cntOfLines++;
    }
    for (int i = 0; i < cntOfLines; i++)
    {
        for (int j = 0; j < lines[i].size(); j++)
        {
            cout << lines[i][j];
            if (j + 1 < lines[i].size())
                cout << string(width[j] - lines[i][j].length() + 1, ' ');
        }
        cout << '\n';
    }
    
    return 0;
}
