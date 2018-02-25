// Three Families
// UVa ID: 12502
// Verdict: Accepted
// Submission Date: 2018-02-26
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

    int cases, x, y, z;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> x >> y >> z;
        if (3 * x <= (x + y)) cout << 0 << '\n';
        else if (3 * y <= (x + y)) cout << z << '\n';
        else cout << (2 * x - y) * z / (x + y) << '\n';
    }

    return 0;
}
