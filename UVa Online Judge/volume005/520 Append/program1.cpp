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

    int pi, ri, total, tail, head, current, idx;
    vector<int> cache;

    while (getline(cin, line))
    {
        total = tail = head = 0;

        do
        {
            pi = ri = 0;
            
            idx = 0;
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
            
            if (pi == 0)
            {
                cache.push_back(current);
            }
            else
            {
                
            }
        }
        while (getline(cin, line), line.length() > 0);

        total += (tail - head) - 1;
        cout << total << '\n';

        total = tail = head = current = 0;
        cache.clear();
    }
    
    return 0;
}
