// Gizilch
// UVa ID: 653
// Verdict: Accepted
// Submission Date: 2017-06-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct state
{
    int score;
    vector<int> grapes;
};

bool referee(vector<vector<int>> &possible1, vector<vector<int>> &possible2)
{
    for (int i = 0; i < possible1.size(); i++)
    {
        set<int> used;
        for (int k = 0; k < possible1[i].size(); k++)
            used.insert(possible1[i][k]);
                
        for (int j = 0; j < possible2.size(); j++)
        {
            bool conflicted = false;
            for (int k = 0; k < possible2[j].size(); k++)
                if (used.find(possible2[j][k]) != used.end())
                {
                    conflicted = true;
                    break;
                }
            
            if (!conflicted) return true;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int score1, score2;
    while (cin >> score1 >> score2)
    {
        if (score1 > score2) swap(score1, score2);
        
        vector<vector<int>> possible1, possible2;
        
        queue<state> unvisited;
        unvisited.push(state{score1, vector<int>()});
        while (!unvisited.empty())
        {
            state current = unvisited.front();
            unvisited.pop();
            
            if (current.score == 1) 
            {
                possible1.push_back(current.grapes);
                continue;
            }
            
            int start = 0;
            if (current.grapes.size() > 0) start = current.grapes.back();
            
            for (int i = start + 1; i <= 100; i++)
                if (current.score % i == 0)
                {
                    state next = current;
                    next.score = current.score / i;
                    next.grapes.push_back(i);
                    unvisited.push(next);
                }
        }
        
        unvisited.push(state{score2, vector<int>()});
        while (!unvisited.empty())
        {
            state current = unvisited.front();
            unvisited.pop();
            
            if (current.score == 1)
            {
                possible2.push_back(current.grapes);
                continue;
            }
            
            int start = 0;
            if (current.grapes.size() > 0) start = current.grapes.back();

            for (int i = start + 1; i <= 100; i++)
                if (current.score % i == 0)
                {
                    state next = current;
                    next.score = current.score / i;
                    next.grapes.push_back(i);
                    unvisited.push(next);
                }
        }
        
        if (possible1.size() == 0) cout << score2 << '\n';
        else
        {
            if (possible2.size() == 0) cout << score1 << '\n';
            else
            {
                if (referee(possible1, possible2))
                    cout << score2 << '\n';
                else
                    cout << score1 << '\n';
            }
        }
    }
    
    return 0;
}
