// Commando War
// UVa ID: 11729
// Verdict: Accepted
// Submission Date: 2017-12-03
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

struct soldier
{
    int brief, job;
    bool operator<(const soldier &s) const
    {
        if (job != s.job) return job > s.job;
        return brief < s.brief;
    }
} soldiers[10010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> soldiers[i].brief >> soldiers[i].job;

        sort(soldiers, soldiers + n);

        int total = 0, finished = 0;
        for (int i = 0; i < n; i++)
        {
            total += soldiers[i].brief;
            if (total + soldiers[i].job > finished)
                finished = total + soldiers[i].job;
        }
        cout << "Case " << ++cases << ": " << max(total, finished) << '\n';
    }
 
    return 0;
}
