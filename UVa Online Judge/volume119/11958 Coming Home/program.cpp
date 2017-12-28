// Coming Home
// UVa ID: 11958
// Verdict: Accepted
// Submission Date: 2017-12-28
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

    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int least = 0x3fffffff;

        int k, HH, MM, hh, mm, q;
        char seperator;
        
        cin >> k >> HH >> seperator >> MM;
        int time1 = HH * 60 + MM;

        for (int i = 1; i <= k; i++)
        {
            cin >> hh >> seperator >> mm >> q;
            int time2 = hh * 60 + mm;
            if (time2 < time1) time2 += 1440;
            if (time2 >= time1) least = min(least, time2 - time1 + q);
        }
        
        cout << "Case " << c << ": " << least << '\n';
    }

    return 0;
}
