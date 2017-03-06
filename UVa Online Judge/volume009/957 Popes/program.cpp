// Popes
// UVa ID: 957
// Verdict: Accepted
// Submission Date: 2017-03-06
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

int Y, P, L;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    while (cin >> Y)
    {
        cin >> P;
        
        deque<int> popes;
        int maxCount = 0, maxStart = 0, maxEnd = 0;
        
        cin >> L;
        popes.push_back(L);

        maxCount = 1, maxStart = L, maxEnd = L;
        
        for (int i = 2; i <= P; i++)
        {
            cin >> L;
            if (L - popes.front() < Y)
            {
                popes.push_back(L);
            }
            else
            {
                if (popes.size() > maxCount)
                {
                    maxCount = popes.size(), maxStart = popes.front(), maxEnd = popes.back();
                }

                while (!popes.empty())
                {
                    if (L - popes.front() < Y)
                    {
                        popes.push_back(L);
                        break;
                    }
                    popes.pop_front();
                }
            }
        }

        if (popes.size() > maxCount)
        {
            maxCount = popes.size(), maxStart = popes.front(), maxEnd = popes.back();
        }
      
        cout << maxCount << ' ' << maxStart << ' ' << maxEnd << '\n';
    }
    
    return 0;
}
