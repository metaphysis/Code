// Divisible Group Sums
// UVa ID: 10616
// Verdict: Accepted
// Submission Date: 2017-11-19
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

    int n, q, d, m, number[210], mod[210];
    long long group[210][11][21];
    int cases = 0;

    while (cin >> n >> q, n > 0)
    {
        cout << "SET " << ++cases << ":\n";
        
        for (int i = 1; i <= n; i++)
            cin >> number[i];
        
        for (int i = 1; i <= q; i++)
        {
            cout << "QUERY " << i << ": ";

            cin >> d >> m;
            for (int j = 1; j <= n; j++)
                mod[j] = ((number[j] % d) + d) % d;

            if (m <= n)
            {
                memset(group, 0, sizeof(group));
                group[0][0][0] = 1;
                for (int x = 1; x <= n; x++)
                    for (int y = 0; y <= m; y++)
                        for (int r = 0; r < d; r++)
                        {
                            group[x][y][r] += group[x - 1][y][r];
                            if (y) group[x][y][r] += group[x - 1][y - 1][(r - mod[x] + d) % d];
                        }
                cout << group[n][m][0] << '\n';
            }
            else cout << "0\n";
        }
    }
    
    return 0;
}
