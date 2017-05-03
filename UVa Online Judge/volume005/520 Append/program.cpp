// Append
// UVa ID: 520
// Verdict: Accepted
// Submission Date: 2017-05-02
// UVa Run Time: 0.000s
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

    int pi, ri;
    vector<pair<int, int>> pairs;
    vector<int> indexer;
    string line;

    while (getline(cin, line))
    {
        do
        {
            pi = ri = 0;
            
            int idx = 0;
            while (!isblank(line[idx]))
            {
                pi = pi * 10 + (line[idx] - '0');
                idx++;
            }

            if (pi == 0) ri = 1;
            else
            {
                idx++;
                while (idx < line.length())
                {
                    ri = ri * 10 + (line[idx] - '0');
                    idx++;
                }
            }

            pairs.push_back(make_pair(pi, ri));
            if (pi == 0) indexer.push_back(pairs.size() - 1);
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
