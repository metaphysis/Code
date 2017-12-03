// Perfect Choir
// UVa ID: 12485
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, notes[10010];

    while (cin >> n)
    {
        int total = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> notes[i];
            total += notes[i];
        }
        if (total % n != 0) cout << "-1\n";
        else
        {
            int average = total / n, bar = 0;
            for (int i = 0; i < n; i++)
                if (notes[i] < average)
                    bar += (average - notes[i]);
            cout << (bar + 1) << '\n';
        }
    }

    return 0;
}
