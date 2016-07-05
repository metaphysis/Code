// Transferable Voting (II)
// UVa IDs: 349
// Verdict: Accepted
// Submission Date: 2016-07-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int c, n, cases = 0;
    while (cin >> c >> n)
    {
        if (c == 0 && n == 0) break;
        
        assert(c > 0 && n > 0);
        
        int selected, invalidVotes = 0;
        vector<vector<int>> votes;
        
        for (int i = 1; i <= n; i++)
        {
            set<int> cache;
            vector<int> aVote;
            
            bool invalid = false;
            for (int j = 1; j <= c; j++)
            {
                cin >> selected;
                if (selected > c || selected == 0 || cache.count(selected) > 0)
                    invalid = true;
                else
                {    
                    aVote.push_back(selected);
                    cache.insert(selected);
                }
            }
            
            if (invalid)
                invalidVotes++;
            else
                votes.push_back(aVote);
        }
        
        cout << "Election #" << ++cases << endl;
        if (invalidVotes > 0)
            cout << "   " << invalidVotes << " bad ballot(s)" << endl;
        
        if (c == 1)
        {
            cout << "   Candidate 1 is elected." << endl;
            continue;
        }
        
        map<int, int> voteCounter;
        int totalVotes = votes.size() / 2 + 1;

        while (true)
        {
            int lowest = votes.size();
            voteCounter.clear();
            
            for (int i = 0; i < votes.size(); i++)
                if (votes[i].size())
                    voteCounter[votes[i].front()]++;

            bool winnerIsHere = false;
            for (auto counter : voteCounter)
            {
                lowest = min(lowest, counter.second);
                if (counter.second >= totalVotes)
                {
                    winnerIsHere = true;
                    cout << "   Candidate " << counter.first << " is elected." << endl;
                    break;
                }
            }

            if (winnerIsHere)
                break;
            
            bool tie = true;
            for (auto counter : voteCounter)
                if (counter.second != lowest)
                {
                    tie = false;
                    break;
                }
                
            if (tie)
            {
                cout << "   The following candidates are tied:";
                for (auto counter : voteCounter)
                    cout << " " << counter.first;
                cout << endl;
                break;
            }
            
            for (auto counter : voteCounter)
                if (counter.second == lowest)
                {
                    for (int i = 0; i < votes.size(); i++)
                        if (votes[i].front() == counter.first)
                            votes[i].erase(votes[i].begin());
                    break;
                }
        }
    }
    
	return 0;
}
