// Bar Codes
// UVa ID: 10721
// Verdict: Accepted
// Submission Date: 2018-01-20
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

long long bc[51][51][51] = {0};

long long search(int n, int k, int m)
{
    if (n == 0 && k == 0) return 1;
    if (n == 0 || k == 0) return 0;
    if (bc[n][k][m] < 0)
    {
        bc[n][k][m] = 0;
        for (int i = 1; i <= m; i++)
        {
            if (n - i < 0) break;
            bc[n][k][m] += search(n - i, k - 1, m);
        }
    }
    return bc[n][k][m];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(bc, -1, sizeof(bc));

    int n, k, m;
    while (cin >> n >> k >> m)
    {
        search(n, k, m);
        cout << bc[n][k][m] << '\n';
    }
    
    return 0;
}
