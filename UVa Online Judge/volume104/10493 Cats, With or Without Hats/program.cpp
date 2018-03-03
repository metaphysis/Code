// Cats, With or Without Hats
// UVa ID: 10493
// Verdict: Accepted
// Submission Date: 2018-03-03
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

    int n, m;
    while (cin >> n >> m, n > 0)
    {
        cout << n << ' ' << m << ' ';
        if (n == 1 && m == 1) cout << "Multiple\n";
        else if (n == 1 && m != 1) cout << "Impossible\n";
        else if ((m - 1) % (n - 1) == 0) cout << (m - 1) / (n - 1) + m << '\n';
        else cout << "Impossible\n";
    }

    return 0;
}
