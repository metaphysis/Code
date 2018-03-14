// Parking Lot
// UVa ID: 603
// Verdict: Accepted
// Submission Date: 2016-08-30
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second > b.second;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, car, empty, advanced;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1)
            cout << '\n';

        map<int, int> arranged;
        vector<pair<int, int>> wait;
        vector<int> autos;

        while (cin >> car, car != 99)
        {
            wait.push_back(make_pair(car, car - 1));
            autos.push_back(car);
        }
        
        string line;
        cin.ignore(1024, '\n');
        while (getline(cin, line), line.length() > 0)
        {
            if (wait.size() == 0)
                continue;

            sort(wait.begin(), wait.end(), cmp);
            
            empty = stoi(line) - 1;
            if (empty < wait.back().second)
            {
                advanced = empty + 20 - wait.front().second;
                arranged[wait.front().first] = empty;
                wait.erase(wait.begin());
            }
            else
            {
                for (int i = 0; i < wait.size(); i++)
                    if (empty >= wait[i].second)
                    {
                        advanced = empty - wait[i].second;
                        arranged[wait[i].first] = empty;
                        wait.erase(wait.begin() + i);
                        break;
                    }
            }
            
            for (int i = 0; i < wait.size(); i++)
                wait[i].second = (wait[i].second + advanced) % 20;
        }
        
        for (int i = 0; i < autos.size(); i++)
        {
            cout << "Original position " << autos[i] << ' ';
            if (arranged.find(autos[i]) != arranged.end())
                cout << "parked in " << arranged[autos[i]] + 1 << '\n';
            else
                cout << "did not park\n";
        }
        
    }
    
	return 0;
}
