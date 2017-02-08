// Trial of the Millennium
// UVa ID: 431
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct evidence
{
    int index, score, hour;
    string description;
    
    bool operator<(const evidence &data) const
    {
        if (hour != data.hour)
            return hour < data.hour;
        else if (score != data.score)
            return score > data.score;
        else
            return index < data.index;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    int scores[110][250], choices[110][250], n;
        
    getline(cin, line);
    int cases = stoi(line);
    
    getline(cin, line);
    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line);
        int time_limit = stoi(line);
        
        vector<evidence> evidences;
        int count = 1;
        while (getline(cin, line), line.length() > 0)
        {
            evidence data;
            
            data.index = count++;

            istringstream iss(line);
            iss >> data.score >> data.hour;
            getline(iss, data.description);
            data.description.erase(data.description.begin());
            
            evidences.push_back(data);
        }
        
        if (c > 1) cout << '\n';

        sort(evidences.begin(), evidences.end());
        evidence empty;
        evidences.insert(evidences.begin(), empty);

        memset(scores, 0, sizeof(scores));
        memset(choices, 0, sizeof(choices));
        n = evidences.size() - 1;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= time_limit; j++)
            {
                if (j >= evidences[i].hour && scores[i - 1][j - evidences[i].hour] + evidences[i].score > scores[i - 1][j])
                {
                    choices[i][j] = 1;
                    scores[i][j] = scores[i - 1][j - evidences[i].hour] + evidences[i].score;
                }
                else scores[i][j] = scores[i - 1][j];
            }
        
        vector<int> selected;
        int last_index = n, pre_time_limit = time_limit;
        int used_hours = 0, max_points = 0;

        while (last_index > 0)
        {
            if (choices[last_index][pre_time_limit])
            {
                selected.push_back(last_index);
                pre_time_limit -= evidences[last_index].hour;
                used_hours += evidences[last_index].hour;
                max_points += evidences[last_index].score;
            }
            last_index--;
        }
        reverse(selected.begin(), selected.end());

        if (max_points == 0)
        {
            cout << "There is not enough time to present any evidence. Drop the charges.\n";
            continue;
        }
        
        cout << "Score  Time  Description\n";
        cout << "-----  ----  -----------\n";
        for (auto item : selected)
        {
            cout << setw(3) << right << evidences[item].score;
            cout << "    ";
            cout << setw(3) << right << evidences[item].hour;
            cout << "   ";
            cout << evidences[item].description << '\n';
        }
        cout << '\n';

        cout << "Total score: " << max_points << " points\n";
        cout << " Total time: " << used_hours << " hours\n";
    }
    
	return 0;
}
