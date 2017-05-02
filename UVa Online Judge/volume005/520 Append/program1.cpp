// Append
// UVa ID: 520
// Verdict: Accepted
// Submission Date: 2017-05-02
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int p, r;
    string ri;
    vector<pair<int, int>> pairs;
    vector<int> indexer;
    istringstream iss;
    string line;

    while (getline(cin, line))
    {
        do
        {
            iss.clear(), iss.str(line);
            iss >> p >> ri;
            
            if (p == 0) r = 1;
            else  r = stoi(ri);

            pairs.push_back(make_pair(p, r));
            if (p == 0) indexer.push_back(pairs.size() - 1);
        }
        while (getline(cin, line), line.length() > 0);
        
        int total = 0, lastCheckPoint = pairs.size();
        for (auto it = indexer.rbegin(); it != indexer.rend(); it++)
        {
            int start = *it, end = lastCheckPoint, length = 0;

            if (start == 0) continue;

            for (int i = start; i < end; i++)
            {
                if (pairs[i].first <= length)
                    length += pairs[i].second;
                else
                {
                    length = -1;
                    break;
                }
            }
            
            if (length >= 0)
            {
                lastCheckPoint = start;
                total++;
            }
        }

        cout << total << '\n';

        pairs.clear(), indexer.clear();
    }
    
    return 0;
}
