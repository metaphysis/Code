// Bowling
// UVa ID: 584
// Verdict: Accepted
// Submission Date: 2016-08-17
// UVa Run Time: 0.160s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line), line != "Game Over")
    {
        vector<int> scores;
        char pins;
        
        string text;
        istringstream iss(line);
        while (iss >> pins)
        {
            if (pins == '/')
                scores.push_back(10 - scores.back());
            else if (pins == 'X')
                scores.push_back(10);
            else
                scores.push_back(pins - '0');
                
            text += pins;
        }
        
        int total = 0, frames = 0;
        for (int i = 0, rolls = 0; i < text.length() && frames < 10; i++)
        {
            total += scores[i];

            if (text[i] == 'X')
            {
                total += scores[i + 1];
                total += scores[i + 2];
                rolls = 0;
                frames++;
            }
            else if (text[i] == '/')
            {
                total += scores[i + 1];
                rolls = 0;
                frames++;
            }
            else
            {
                rolls++;
                if (rolls == 2)
                {
                    frames++;
                    rolls = 0;
                }
            }
            
            cout << text[i] << ' ' << total << '\n';
        }
        
        cout << total << '\n';
    }
    
	return 0;
}
