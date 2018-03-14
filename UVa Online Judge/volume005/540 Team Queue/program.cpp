// Team Queue
// UVa ID: 540
// Verdict: Accepted
// Submission Date: 2016-08-10
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int t, cases = 0, total, number, teams[1000000];
    while (cin >> t, t)
    {
        cout << "Scenario #" << ++cases << '\n';

        for (int i = 1; i <= t; i++)
        {
            cin >> total;
            for (int j = 1; j <= total; j++)
            {
                cin >> number;
                teams[number] = i;
            }
        }

        list<int> teamates[1001], indexer;

        string command;
        while (cin >> command, command != "STOP")
        {
            if (command == "ENQUEUE")
            {
                cin >> number;
                if (teamates[teams[number]].size() == 0)
                    indexer.push_back(teams[number]);
                teamates[teams[number]].push_back(number);
            }
            else
            {
                if (indexer.size() > 0)
                {
                    int index = indexer.front();
                    cout << teamates[index].front() << '\n';
                    teamates[index].erase(teamates[index].begin());
                    if (teamates[index].size() == 0)
                        indexer.erase(indexer.begin());
                }
            }
        }
        
        cout << '\n';
    }
    
	return 0;
}
