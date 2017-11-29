// Helping Fill Bates
// UVa ID: 10567
// Verdict: Accepted
// Submission Date: 2017-11-29
// UVa Run Time: 0.010s
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

    char c;
    int idx = 0, q;
    string SS;
    vector<int> indices[257];

    while (cin.read(&c, 1) and c != '\n') indices[c].push_back(idx++);

    cin >> q;
    for (int c = 1; c <= q; c++)
    {
        cin >> SS;

        int first = 0, last = -1, flag = 1;
        for (int i = 0; i < SS.length(); i++)
        {
            auto j = upper_bound(indices[SS[i]].begin(), indices[SS[i]].end(), last);
            if (j == indices[SS[i]].end())
            {
                flag = 0;
                break;
            }
            last = *j;
            if (!i) first = last;
        }

        if (flag) cout << "Matched " << first << ' ' << last << '\n';
        else cout << "Not matched\n";
    }

    return 0;
}
