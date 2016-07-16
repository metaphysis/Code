// Eeny Meeny Moo
// UVa ID: 440
// Verdict: Accepted
// Submission Date: 2016-07-15
// UVa Run Time: 0.180s
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

int n, region[151];

int findCW(int index, int count)
{
    for (int i = index; i < n; i++)
        if (region[i] > 0 && ((--count) == 0))
            return i;

    while (true)
    {
        for (int i = 0; i < n; i++)
            if (region[i] > 0 && ((--count) == 0))
                return i;
    }
}

int findRegion()
{
    for (int i = 0; i < n; i++)
        if (region[i] > 0)
            return region[i];
}

int main(int argc, char* argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    while (cin >> n, n)
    {
        int m = 0;
        while (true)
        {
            for (int i = 1; i <= n; i++)
                region[i - 1] = i;
            
            int total = n, blacked = 0;
            bool found = true;
            
            m++;
            while (total > 1)
            {
                if (region[blacked] == 2)
                {
                    found = false;
                    break;
                }

                region[blacked] = 0;
                total--;

                blacked = (blacked + 1) % n;
                blacked = findCW(blacked, m);
            }
            
            if (found)
                break;
        }
        
        cout << m << endl;
    }
    
    return 0;
}
