// Bar Codes
// UVa ID: 10721
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
    if (bc[n][k][m] < 0)
    {
        if (n == 1)
        {
            if (k > 1) bc[n][k][m] = 0;
            else bc[n][k][m] = 1;
        }
        else if (k == 1)
        {
            if (n > m) bc[n][k][m] = 0;
            else bc[n][k][m] = 1;
        }
        else if (m == 1)
        {
            bc[n][k][m] = 2 * search(n - 1, k - 1, m);
        }
        else
        {
            if (m > n) m = n;
            bc[n][k][m] = k * search(n, k, m - 1);
        }
    }

    cout << "n = " << n << " k = " << k << " m = " << m << ": " << bc[n][k][m] << '\n';
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
