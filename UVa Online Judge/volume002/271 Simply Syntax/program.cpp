// Simply Syntax
// UVa ID: 271
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.060s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int NONE = -1, N = 0, C = 1, D = 2, E = 3, I = 4, SENTENCE = 5;

vector<int> S;

int T[5][4] = {
    {SENTENCE, C, SENTENCE, SENTENCE},
    {SENTENCE, D, SENTENCE, SENTENCE},
    {SENTENCE, E, SENTENCE, SENTENCE},
    {SENTENCE, I, SENTENCE, SENTENCE},
    {N, NONE, SENTENCE, SENTENCE}
};

void translateToSymbol(string line)
{
    S.clear();
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == 'N')
            S.push_back(N);
        else if (line[i] == 'C')
            S.push_back(C);
        else if (line[i] == 'D')
            S.push_back(D);
        else if (line[i] == 'E')
            S.push_back(E);
        else if (line[i] == 'I')
            S.push_back(I);
        else
            S.push_back(SENTENCE);
    }
}

bool isSentence(string line)
{
    translateToSymbol(line);

    while (true)
    {
        bool replaced = false;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < S.size(); )
            {
                if ((S[j] != T[i][0]) ||
                    (~T[i][1] && (!j || S[j - 1] != T[i][1])) ||
                    (~T[i][2] && (j == (S.size() - 1) || S[j + 1] != T[i][2])))
                {
                    j++;
                    continue;
                }
                j = ~T[i][1] ? S.erase(S.begin() + j - 1) - S.begin() : j;
                j = ~T[i][2] ? S.erase(S.begin() + j + 1) - S.begin() - 1 : j;
                S[j] = T[i][3];
                
                replaced = true;
            }
        }
        
        if (replaced == false)
                break;
    }
    
    return S.size() == 1 && S.front() == SENTENCE;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
        cout << (isSentence(line)? "YES" : "NO") << endl;

    return 0;
}
