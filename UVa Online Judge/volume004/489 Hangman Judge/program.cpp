// Hangman Judge
// UVa ID: 489
// Verdict: Accepted
// Submission Date: 2016-07-14
// UVa Run Time: 0.580s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int round;
    string solution, guess;
    while (cin >> round, round != -1)
    {
        cout << "Round " << round << endl;
        cin >> solution >> guess;
        
        bool flag = false;
        set<char> right, wrong, all;
        for (int i = 0; i < solution.length(); i++)
            all.insert(solution[i]);
        
        for (int i = 0; i < guess.length(); i++)
        {
            if (right.find(guess[i]) != right.end()) continue;
            
            if (all.find(guess[i]) == all.end())
            {
                wrong.insert(guess[i]);
                if (wrong.size() >= 7)
                {
                    cout << "You lose." << endl;
                    flag = true;
                    break;
                }
            }
            else
            {
                right.insert(guess[i]);
                all.erase(guess[i]);
                if (all.size() == 0)
                {
                    cout << "You win." << endl;
                    flag = true;
                    break;
                }
            }
        }
        
        if (!flag) cout << "You chickened out." << endl;
    }
    
	return 0;
}
