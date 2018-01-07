// Demanding Dilemma
// UVa ID: 11550
// Verdict: Accepted
// Submission Date: 2018-01-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

    int cases, n, m, start[100], end[100], mij;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;

        memset(start, 0, sizeof(start));
        memset(end, 0, sizeof(end));

        bool safe = true;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                cin >> mij;
                if (mij == 1)
                {
                    if (start[j] == 0) start[j] = i;
                    else if (end[j] == 0) end[j] = i;
                    else
                    {
                        safe = false;
                    }
                }
            }
            
        if (safe)
        {
            for (int i = 1; i <= m; i++)
                if (start[i] == 0 || end[i] == 0)
                {
                    safe = false;
                    break;
                }
        }
        
        if (safe)
        {
            for (int i = 1; i <= m; i++)
            {
                for (int j = i + 1; j <= m; j++)
                    if (start[i] == start[j] && end[i] == end[j] ||
                        start[i] == end[j] && end[i] == start[j])
                    {
                        safe = false;
                        break;
                    }
                if (safe == false) break;
            }
        }

        cout << (safe ? "Yes" : "No") << '\n';
    }

    return 0;
}
