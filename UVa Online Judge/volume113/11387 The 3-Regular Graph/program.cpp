// The 3-Regular Graph
// UVa ID: 11387
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        if (n <= 2 || (n % 2 == 1)) cout << "Impossible\n";
        else
        {
            cout << 3 * n / 2 << '\n';
            for (int i = 1; i <= n; i++)
            {
                int j = (i + 1) % n;
                if (j == 0) j = n;
                cout << i << ' ' << j << '\n';
            }
            for (int i = 1; i < n - 1; i++)
            {
                int j = (i + 2) % n;
                if (j == 0) j = n;
                cout << i << ' ' << j << '\n';
            }
        }
    }

    return 0;
}
