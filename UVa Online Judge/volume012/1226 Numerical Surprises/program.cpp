// Numerical Surprises
// UVa ID: 1226
// Verdict: Accepted
// Submission Date: 2018-03-02
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

    int cases, N;
    string P;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> P;
        int r = 0;
        for (auto d : P)
        {
            r = (r << 3) + (r << 1) + d - '0';
            r %= N;
        }
        cout << r << '\n';
    }

    return 0;
}
