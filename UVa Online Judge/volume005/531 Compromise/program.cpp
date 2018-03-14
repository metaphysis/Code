// Compromise
// UVa ID: 531
// Verdict: Accepted
// Submission Date: 2016-08-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string first[110], second[110];
    int commom[110][110][2] = { 0 };

    while (true)
    {
        string word;
        
        int first_count = 1;
        while (cin >> word)
        {
            if (word == "#")
                break;
            first[first_count++] = word;
        }
            
        int second_count = 1;
        while (cin >> word)
        {
            if (word == "#")
                break;
            second[second_count++] = word;
        }
            
        if (first_count == 1)
            break;
            
        memset(commom, 0, sizeof(commom));
        
        for (int i = 1; i < first_count; i++)
            for (int j = 1; j < second_count; j++)
            {
                if (first[i] == second[j] && (commom[i - 1][j - 1][0] + 1) > commom[i][j][0])
                {
                    commom[i][j][0] = commom[i - 1][j - 1][0] + 1;
                    commom[i][j][1] = 1;
                }
                
                if (commom[i - 1][j][0] > commom[i][j][0])
                {
                    commom[i][j][0] = commom[i - 1][j][0];
                    commom[i][j][1] = 2;
                }
                
                if (commom[i][j - 1][0] > commom[i][j][0])
                {
                    commom[i][j][0] = commom[i][j - 1][0];
                    commom[i][j][1] = 3;
                }
            }
        
        vector<string> words;
        int endi = first_count - 1, endj = second_count - 1;
        while (commom[endi][endj][1] > 0)
        {
            if (commom[endi][endj][1] == 1)
            {
                words.push_back(first[endi]);
                endi -= 1, endj -= 1;
            }
            else if (commom[endi][endj][1] == 2)
                endi -= 1;
            else if (commom[endi][endj][1] == 3)
                endj -= 1;
        }
        
        reverse(words.begin(), words.end());
        for (int i = 0; i < words.size(); i++)
        {
            if (i > 0)
                cout << ' ';
            cout << words[i];
        }
        cout << '\n';
    }
    
	return 0;
}
