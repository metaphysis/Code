// Checkers
// UVa ID: 11957
// Verdict: Accepted
// Submission Date: 2018-02-22
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

const int MOD = 1000007;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char board[110][110];
    int cases, n, cnt[110][110], r;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                cnt[i][j] = 0;
                cin >> board[i][j];
                if (board[i][j] == '.' && i == 1) cnt[i][j] = 1;
            }

        int result = -1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (board[i][j] != 'B')
                {
                    if (i - 1 >= 1 && j - 1 >= 1)
                    {
                        if (board[i - 1][j - 1] == '.')
                            cnt[i][j] = (cnt[i][j] + cnt[i - 1][j - 1]) % MOD;
                        else
                        {
                            if (i - 2 >= 1 && j - 2 >= 1)
                                cnt[i][j] = (cnt[i][j] + cnt[i - 2][j - 2]) % MOD;
                        }
                    }
                    if (i - 1 >= 1 && j + 1 <= n)
                    {
                        if (board[i - 1][j + 1] == '.')
                            cnt[i][j] = (cnt[i][j] + cnt[i - 1][j + 1]) % MOD;
                        else
                        {
                            if (i - 2 >= 1 && j + 2 <= n)
                                cnt[i][j] = (cnt[i][j] + cnt[i - 2][j + 2]) % MOD;
                        }
                    }
                }
                if (board[i][j] == 'W')
                {
                    result = cnt[i][j];
                    break;
                }
            }
            if (result >= 0) break;
        }

        cout << "Case " << c << ": " << result << '\n';
    }

    return 0;
}
