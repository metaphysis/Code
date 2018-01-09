// Rotated Square
// UVa ID: 10855
// Verdict: Accepted
// Submission Date: 2018-01-09
// UVa Run Time: 0.020s
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

int N, n;
char bigger[110][110], smaller[110][110], temp[110][110];

void rotate90()
{
    for (int i = n, k = 1; i >= 1; i--, k++)
        for (int j = 1; j <= n; j++)
            temp[j][k] = smaller[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            smaller[i][j] = temp[i][j];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    while (cin >> N >> n)
    {
        if (N == 0) break;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                cin >> bigger[i][j];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> smaller[i][j];

        for (int c = 1; c <= 4; c++)
        {
            int cnt = 0;
            for (int i = 1; i <= (N - n) + 1; i++)
                for (int j = 1; j <= (N - n) + 1; j++)
                {
                    bool same = true;
                    for (int k = 0; k < n; k++)
                        for (int l = 0; l < n; l++)
                            if (bigger[i + k][j + l] != smaller[k + 1][l + 1])
                            {
                                same = false;
                                goto next;
                            }
                    next:
                    if (same) cnt++;
                }
            if (c > 1) cout << ' ';
            cout << cnt;
            rotate90();
        }
        cout << '\n';
    }

    return 0;
}
