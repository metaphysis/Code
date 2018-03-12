// Rare Easy Problem
// UVa ID: 10633
// Verdict: Accepted
// Submission Date: 2018-03-12
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

    unsigned long long n;
    while (cin >> n, n > 0)
    {
        unsigned long long x = n * 10 / 9;
        vector<unsigned long long> r;
        r.insert(r.begin(), x);

        while (true)
        {
            x--;
            if (x - x / 10 == n) r.insert(r.begin(), x);
            else break;
        }
        for (int i = 0; i < r.size(); i++)
        {
            if (i) cout << ' ';
            cout << r[i];
        }
        cout << '\n';
    }

    return 0;
}
